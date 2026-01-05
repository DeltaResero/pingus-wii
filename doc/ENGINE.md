# Engine Technical Notes

## Rendering Layers (Z-Position)

The engine uses Z-positions to determine drawing order (painters algorithm).

* **-100**: Background objects (drawn first, behind everything).
* **0**: Ground (The main playfield).
* **75**: Pingus (The characters).
* **100**: Foreground objects (Liquids, weather, etc).

## Physics Logic

### Wall Detection

Pingus can step over obstacles up to 2 pixels high. Obstacles 3 pixels or higher
act as a wall and cause them to reverse direction.
