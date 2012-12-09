#include "Actor.h"

// METHOD STUB TO SHOW FUNCTIONALITY
ActorComponent * createVisualComponent()
{
	return (ActorComponent *)(new VisualComponent());
}
ActorComponent * createTestComponent1()
{
	return (ActorComponent *)(new TestComponent1());
}
ActorComponent * createTestComponent2()
{
	return (ActorComponent *)(new TestComponent2());
}

ActorFactory::ActorFactory() : lastActorId(0)
{
	componentCreatorMap["Visual"] = createVisualComponent;
	componentCreatorMap["Test1"] = createTestComponent1;
	componentCreatorMap["Test2"] = createTestComponent2;
}


Actor * ActorFactory::createActor(const char *actorFilename)
{
	// Get the base actor element
	XMLDoc doc;
	doc.LoadFile(actorFilename);
	XMLElement *actorData = doc.FirstChildElement("Actor");
	Actor *actor = new Actor;
	actor->init(actorData);
	actor->actorId = getNextActorId();


	// For each component of the actor
	for (XMLElement *compData = actorData->FirstChildElement(); compData != NULL;
			compData = compData->NextSiblingElement())
	{
		// Create the component and set its owner to the actor
		ActorComponent *comp = createActorComponent(compData);
		comp->postInit();
		actor->addComponent(comp);
	}

	actor->postInit();
	return actor;
}

ActorComponent * ActorFactory::createActorComponent(XMLElement *xmlData)
{
	// Create and initialize this component with the given XML data.
	string name = xmlData->Name();
	ActorComponent *component = componentCreatorMap[name]();
	component->init(xmlData);

	return component;
}



