// Переписанный на языке C++ пример https://github.com/1vanK/Urho3DHabrahabr01/blob/master/Data/Scripts/Main.as

#include "Urho3DAll.h"

class Game : public Application
{
    URHO3D_OBJECT(Game, Application);

private:
    // Указатель на сцену.
    Scene* scene_;

public:
    Game(Context* context) : Application(context)
    {
    }

    void Start()
    {
        // Создаем сцену и добавляем к ней компонент Octree.
        scene_ = new Scene(context_);
        scene_->CreateComponent<Octree>();

        // Создаем ноду и прикрепляем к ней камеру.
        auto cameraNode = scene_->CreateChild("MyCamera");
        auto camera = cameraNode->CreateComponent<Camera>();
        cameraNode->SetPosition(Vector3(0.0f, 0.0f, -5.0f));

        // Указываем движку какая камера какой сцены будет показываться на экране.
        auto viewport = new Viewport(context_, scene_, camera);
        GetSubsystem<Renderer>()->SetViewport(0, viewport);

        // Добавляем в сцену куб.
        auto boxNode = scene_->CreateChild("MyBox");
        auto boxObject = boxNode->CreateComponent<StaticModel>();
        auto cache = GetSubsystem<ResourceCache>();
        boxObject->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
        boxNode->SetRotation(Quaternion(45.0f, 45.0f, 45.0f));

        // Создаем ноду и прикрепляем к ней источник света.
        auto lightNode = scene_->CreateChild("MyLight");
        auto light = lightNode->CreateComponent<Light>();
        light->SetLightType(LIGHT_DIRECTIONAL);
        lightNode->SetDirection(Vector3(0.6f, -0.6f, 0.8f));

        // Определяем функцию, которая будет вызываться каждый кадр.
        SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(Game, HandleUpdate));
    }

    // Обработчик события Update.
    void HandleUpdate(StringHash eventType, VariantMap& eventData)
    {
        // Чтобы не писать Update::P_TIMESTEP. В данном случае это не особо важно,
        // но у события может быть больше, чем один параметр.
        using namespace Update;

        // Сколько времени прошло с предыдущего кадра.
        float timeStep = eventData[P_TIMESTEP].GetFloat();

        // Находим и поворачиваем ноду с кубом.
        auto boxNode = scene_->GetChild("MyBox");
        boxNode->Rotate(Quaternion(10.0f * timeStep, 10.0f * timeStep, 10.0f * timeStep));
    }
};

URHO3D_DEFINE_APPLICATION_MAIN(Game)
