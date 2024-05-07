#include "Loop.h"

std::vector<Player> entity_loop::player_list;

bool entity_loop::start()
{
    std::thread update_thread(entity_loop::loop);

    update_thread.detach();

    return true;
}

void entity_loop::loop() 
{

    std::vector<Player> temp;

    while (true)
    {
        temp.clear();

        uintptr_t localPlayer = driver::read<uintptr_t>(shared::game::client + offsets::dwLocalPlayerPawn);
        int localTeam;
        if (settings::misc::only_enemies)
            localTeam = driver::read<int>(localPlayer + offsets::m_iTeamNum);

        if (settings::triggerbot::enable)
        {
            int entityId = driver::read<int>(localPlayer + offsets::m_iIDEntIndex);
            if (entityId > 0)
            {
                uintptr_t entList = driver::read<uintptr_t>(shared::game::client + offsets::dwEntityList);
                uintptr_t entEntry = driver::read<uintptr_t>(entList + 0x8 * (entityId >> 9) + 0x10);
                uintptr_t entity = driver::read<uintptr_t>(entEntry + 120 * (entityId & 0x1FF));

                if (settings::misc::only_enemies)
                {
                    int entityTeam = driver::read<int>(entity + offsets::m_iTeamNum);

                    if (entityTeam != localTeam)
                    {
                        int entityHp = driver::read<int>(entity + offsets::m_iHealth);
                        shared::triggetbot::onCrosshair = (entityHp > 0);
                    }
                    else {
                        shared::triggetbot::onCrosshair = false;
                    }
                }
                else if (!settings::misc::only_enemies)
                {
                    int entityHp = driver::read<int>(entity + offsets::m_iHealth);
                    shared::triggetbot::onCrosshair = (entityHp > 0);
                }
                else {
                    shared::triggetbot::onCrosshair = false;
                }
            }
            else {
                shared::triggetbot::onCrosshair = false;
            }
        }

        uintptr_t entity_list = driver::read<uintptr_t>(shared::game::client + offsets::dwEntityList);

        if (!entity_list || entity_list == 0)
        {
            Log("\n[-]", "Game is closed", RED);
            system("pause");
            exit(1);
        }

        vector3 Localorigin = driver::read<vector3>(localPlayer + offsets::m_vecOrigin);
        view_matrix_t view_matrix = driver::read<view_matrix_t>(shared::game::client + offsets::dwViewMatrix);

        for (int i = 0; i < 32; ++i)
        {
            Player tempPlayer;
            uintptr_t listEntry = driver::read<uintptr_t>(entity_list + (8 * (i & 0x7FFF) >> 9) + 16);
            if (!listEntry) continue;
            uintptr_t player = driver::read<uintptr_t>(listEntry + 120 * (i & 0x1FF));
            if (!player) continue;
            uintptr_t playerPawn = driver::read<uintptr_t>(player + offsets::m_hPlayerPawn);
            uintptr_t listEntry2 = driver::read<uintptr_t>(entity_list + 0x8 * ((playerPawn & 0x7FFF) >> 9) + 16);
            if (!listEntry2) continue;
            uintptr_t pCSPlayerPawn = driver::read<uintptr_t>(listEntry2 + 120 * (playerPawn & 0x1FF));
            if (!pCSPlayerPawn) continue;
            if (pCSPlayerPawn == localPlayer) continue;

            if (settings::misc::only_enemies)
            {
                int team = driver::read<int>(pCSPlayerPawn + offsets::m_iTeamNum);
                if (team == localTeam) continue;
            }

            int health = driver::read<int>(pCSPlayerPawn + offsets::m_iHealth);
            if (health <= 0 || health > 100) continue;

            if (settings::misc::only_visible) 
            {
                bool e_spotted = driver::read<bool>(pCSPlayerPawn + offsets::m_entitySpottedState + offsets::m_bSpottedByMask);
                bool local_spotted = driver::read<bool>(localPlayer + offsets::m_entitySpottedState + offsets::m_bSpottedByMask);

                bool visible = e_spotted && (1 << local_spotted);

                if (!visible) continue;
            }

            uintptr_t gamescene = driver::read<uintptr_t>(pCSPlayerPawn + 0x318);

            uintptr_t bonearray = driver::read<uintptr_t>(gamescene + 0x160 + 0x80);

            vector3 bone = driver::read<vector3>(bonearray + settings::misc::bone * 32);
            
            if (!world_to_screen(
                shared::game::screen_size,
                bone,
                tempPlayer.position,
                view_matrix
            ))
                continue;

            if (tempPlayer.position.x <= 0 || tempPlayer.position.y <= 0) continue;

            if (tempPlayer.position.x < shared::game::screen_size.x || tempPlayer.position.y < shared::game::screen_size.y)
            {
                temp.push_back(tempPlayer);
            }
        }
        
        player_list.clear();
        player_list = temp;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
};