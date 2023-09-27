#include <pch.h>
#include "Projects/ProjectOne.h"
#include "Agent/CameraAgent.h"

#define NUM_OF_GRASSES 50
#define NUM_OF_DEER 25
#define NUM_OF_TIGERS 3
#define NUM_OF_BIRDS 1
#define NUM_OF_HUNTERS 1

void ProjectOne::setup()
{
   // Create your inital agents //

   // Create hunter that shoots at tigers and birds.
   for (int i = 0; i < NUM_OF_HUNTERS; i++)
   {
      Agent* hunter = agents->create_behavior_agent("Hunter", BehaviorTreeTypes::Hunter);
      Vec3 pos = RNG::world_position();
      hunter->set_position(pos);
      hunter->set_specific_scaling(Vec3(2.0f, 2.0f, 2.0f));
      hunter->set_color(Vec3(1.0f, 1.0f, 1.0f));
   }

   // Create bird that flies towards the players cursor, but will be stunned for a second if the mouse is clicked.
   for (int i = 0; i < NUM_OF_BIRDS; i++)
   {
      Agent* bird = agents->create_behavior_agent("Bird", BehaviorTreeTypes::Bird);
      Vec3 pos = RNG::world_position();
      pos.y = 20;
      bird->set_position(pos);
      bird->set_specific_scaling(Vec3(1.5f, 0.25f, 1.5f));
      bird->set_color(Vec3(0.0f, 0.0f, 1.0f));
   }

   // Create deer that eat grass and avoid tigers
   for (int i = 0; i < NUM_OF_DEER; i++)
   {
      Agent* deer = agents->create_behavior_agent("Deer", BehaviorTreeTypes::Deer);

      deer->set_position(RNG::world_position());
      deer->set_specific_scaling(Vec3(1.5f, 1.5f, 1.5f));
      deer->set_color(Vec3(0.8f, 0.5f, 0.0f));
   }
   

   // Create grass
   for (int i = 0; i < NUM_OF_GRASSES; i++)
   {
      Agent* grass = agents->create_behavior_agent("Grass", BehaviorTreeTypes::Grass);
      grass->set_position(RNG::world_position());
      grass->set_specific_scaling(Vec3(1.0f, 0.25f, 1.0f));
      grass->set_yaw(RNG::range(0.0f, 3.0f));
      grass->set_color(Vec3(0.0f, 0.8f, 0.0f));
   }


   // Create tiger that hunts deer.
   for (int i = 0; i < NUM_OF_TIGERS; i++)
   {
      Agent* tiger = agents->create_behavior_agent("Tiger", BehaviorTreeTypes::Tiger);
      tiger->set_position(RNG::world_position());
      tiger->set_specific_scaling(Vec3(2.0f, 2.0f, 2.0f));
      tiger->set_color(Vec3(1.0f, 0.0f, 0.0f));
   }

   // Create player
   //agents->create_behavior_agent("Player", BehaviorTreeTypes::Example);


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
   //camera->set_position(Vec3(-62.0f, 70.0f, terrain->mapSizeInWorld * 0.5f));
   //camera->set_pitch(0.610865); // 35 degrees
   camera->set_position(Vec3(50.0f, 150.0f, 50.0f));
   camera->set_pitch(1.565f);

   audioManager->SetVolume(0.5f);
   audioManager->PlaySoundEffect(L"Assets\\Audio\\retro.wav");
   // uncomment for example on playing music in the engine (must be .wav)
   // audioManager->PlayMusic(L"Assets\\Audio\\motivate.wav");
   // audioManager->PauseMusic(...);
   // audioManager->ResumeMusic(...);
   // audioManager->StopMusic(...);
}