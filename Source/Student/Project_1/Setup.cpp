#include <pch.h>
#include "Projects/ProjectOne.h"
#include "Agent/CameraAgent.h"

#define NUM_OF_GRASSES 50

void ProjectOne::setup()
{
    // Create your inital agents
    agents->create_behavior_agent("Player", BehaviorTreeTypes::Player);

    // Create grass
    for(int i = 0; i < NUM_OF_GRASSES; i++)
       agents->create_behavior_agent("Grass", BehaviorTreeTypes::Grass);

    // Make it actually look like grass, and place it randomly around the map.
    std::vector<Agent*> grasses = agents->get_all_agents_by_type("Grass");
    for (int i = 0; i < grasses.size(); i++)
    {
       grasses[i]->set_position(RNG::world_position());
       grasses[i]->set_specific_scaling(Vec3(1.0f, 0.25f, 1.0f));
       grasses[i]->set_yaw(RNG::range(0.0f, 3.0f));
       grasses[i]->set_color(Vec3(0.0f, 0.8f, 0.0f));
    }

    

    // Create deer
    agents->create_behavior_agent("Deer", BehaviorTreeTypes::Deer);
    std::vector<Agent*> deer = agents->get_all_agents_by_type("Deer");
    for (int i = 0; i < deer.size(); i++)
    {
       deer[i]->set_position(RNG::world_position());
       deer[i]->set_specific_scaling(Vec3(1.5f, 1.5f, 1.5f));
       deer[i]->set_color(Vec3(0.8f, 0.5f, 0.0f));
    }
    
    // Create bird

    // Create bear

    // Create player


    // you can technically load any map you want, even create your own map file,
    // but behavior agents won't actually avoid walls or anything special, unless you code that yourself
    // that's the realm of project 2 though
    terrain->goto_map(0);

    // you can also enable the pathing layer and set grid square colors as you see fit
    // works best with map 0, the completely blank map
    terrain->pathLayer.set_enabled(true);
    terrain->pathLayer.set_value(0, 0, Colors::Red);

    // camera position can be modified from this default as well
    auto camera = agents->get_camera_agent();
    camera->set_position(Vec3(-62.0f, 70.0f, terrain->mapSizeInWorld * 0.5f));
    camera->set_pitch(0.610865); // 35 degrees

    audioManager->SetVolume(0.5f);
    audioManager->PlaySoundEffect(L"Assets\\Audio\\retro.wav");
    // uncomment for example on playing music in the engine (must be .wav)
    // audioManager->PlayMusic(L"Assets\\Audio\\motivate.wav");
    // audioManager->PauseMusic(...);
    // audioManager->ResumeMusic(...);
    // audioManager->StopMusic(...);
}