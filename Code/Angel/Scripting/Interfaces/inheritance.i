%include <factory.i>

%factory(Renderable*, TextActor, ParticleActor, PhysicsActor, Actor);
%factory(MessageListener*, TextActor, ParticleActor, PhysicsActor, Actor);
%factory(Actor*, TextActor, ParticleActor, PhysicsActor);
