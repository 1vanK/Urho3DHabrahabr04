// Переписанный на языке C++ пример https://github.com/1vanK/Urho3DHabrahabr01/blob/master/Data/Scripts/Main.as

#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Application.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Scene/Scene.h>

using namespace Urho3D;

class Game : public Application
{
    URHO3D_OBJECT(Game, Application);

private:
    // Scene@ scene_;
    SharedPtr<Scene> scene_;

public:
    Game(Context* context) : Application(context)
    {
    }

    void Start()
    {
        // scene_ = Scene();
        scene_ = new Scene(context_);
        
        // scene_.CreateComponent("Octree");
        scene_->CreateComponent<Octree>();

        // Node@ cameraNode = scene_.CreateChild("MyCamera");
        auto cameraNode = scene_->CreateChild("MyCamera");
        
        // cameraNode.CreateComponent("Camera");
        cameraNode->CreateComponent<Camera>();
        
        // cameraNode.position = Vector3(0.0f, 0.0f, -5.0f);
        cameraNode->SetPosition(Vector3(0.0f, 0.0f, -5.0f));

        // Viewport@ viewport = Viewport(scene_, cameraNode.GetComponent("Camera"));
        auto viewport = new Viewport(context_, scene_, cameraNode->GetComponent<Camera>());

        // renderer.viewports[0] = viewport;
        GetSubsystem<Renderer>()->SetViewport(0, viewport);
        
        // Node@ boxNode = scene_.CreateChild("MyBox");
        auto boxNode = scene_->CreateChild("MyBox");

        // StaticModel@ boxObject = boxNode.CreateComponent("StaticModel");
        auto boxObject = boxNode->CreateComponent<StaticModel>();

        // boxObject.model = cache.GetResource("Model", "Models/Box.mdl");
        auto cache = GetSubsystem<ResourceCache>();
        boxObject->SetModel(cache->GetResource<Model>("Models/Box.mdl"));

        // boxNode.rotation = Quaternion(45.0f, 45.0f, 45.0f);
        boxNode->SetRotation(Quaternion(45.0f, 45.0f, 45.0f));

        // Node@ lightNode = scene_.CreateChild("MyLight");
        auto lightNode = scene_->CreateChild("MyLight");
        
        // Light@ light = lightNode.CreateComponent("Light");
        auto light = lightNode->CreateComponent<Light>();
        
        // light.lightType = LIGHT_DIRECTIONAL;
        light->SetLightType(LIGHT_DIRECTIONAL);
        
        // lightNode.direction = Vector3(0.6f, -0.6f, 0.8f);
        lightNode->SetDirection(Vector3(0.6f, -0.6f, 0.8f));

        // SubscribeToEvent("Update", "HandleUpdate");
        SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(Game, HandleUpdate));
    }

    void HandleUpdate(StringHash eventType, VariantMap& eventData)
    {
        // float timeStep = eventData["TimeStep"].GetFloat();
        float timeStep = eventData["TimeStep"].GetFloat();

        // Node@ boxNode = scene_.GetChild("MyBox");
        auto boxNode = scene_->GetChild("MyBox");
        
        // boxNode.Rotate(Quaternion(10.0f * timeStep, 10.0f * timeStep, 10.0f * timeStep));
        boxNode->Rotate(Quaternion(10.0f * timeStep, 10.0f * timeStep, 10.0f * timeStep));
    }
};

URHO3D_DEFINE_APPLICATION_MAIN(Game)
