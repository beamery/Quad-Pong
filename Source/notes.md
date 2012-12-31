Currently working on the human view

- Specifically, just started on the input handling system
	- Events passed in from main to human view based on event type
	- human view has its will with the events

Next Tasks
----------
- Modify renderer to handle batch rendering
- Figure out how to detect memory leaks
- Implement scoreboard

Redesign of Event System
------------------------
- Event listeners used to be specific to event types
	- This caused listeners to only be able to listen to one event type
	- It also caused a lot more overhead in creating new event types
- With the redesign, listeners are generic event listeners
- Rather than simply registering and using the listener type as the 
  event type to register for, event listeners now register for specific
  event types.
	- When these events are triggered, the event manager sends them out
	  as generic events to any listeners which are registered
	- It is the listener's job to convert them into the correct event type
	  for processing