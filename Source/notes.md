Currently working on the human view

- Specifically, just started on the input handling system
	- Events passed in from main to human view based on event type
	- human view has its will with the events

Next Tasks
----------
- Modify renderer to handle batch rendering
- Figure out how to detect memory leaks
- Transform raw input events into game events

Design of Sphere and rectangle components:
------------------------------------------
- Rectangle will be comprised of 4 lines (top, bottom, left, right)
  - Rectangle will also have a position (the center of the rectangle)
- Circle will have position (center of the circle) and a radius
- Collisions between circle and sphere will be handled with a utility method in the 
  collisions section of the physics package
  - Essentially, circle/rectangle collisions will be based on checking collisions with the lines
    of the rectangle and the closest point on the circle
	- For rects oriented vertically/horizontally, this will simply be the circle's radius added to 
	  either its x or y coordinate
	- For non-horizontally oriented rectangles, it's a bit more complicated (don't need to address for quad-pong)