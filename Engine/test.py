import mygameengine
import random
import math
import os
import json
from enum import Enum
from collections import namedtuple

# Constants
SCRN_WIDTH = 240
SCRN_HEIGHT = 240

# It would be ideal to maintain rooms on c++ side but i don't care at this point
rooms = {}
def load_room(rm_name, tileset):
    
    for layer in rooms[rm_name]['layers']:
        if 'objects' in layer:
            for obj in layer['objects']:
                inst = 'o=' + obj['name'] + '(' + str(int(obj['x']))  + ',' + str(int(obj['y'])) + ')'
                exec(inst)
                if 'properties' in obj:
                    for prop in obj['properties']:
                        set_prop = 'o.' + prop['name'] + '=' + str(prop['value'])
                        exec(set_prop)
        if 'data' in layer:
            engine.tilemap_create(tileset, 16, 8, 32, 32, 32, 32, layer['data'])


# Initialize SDL
engine = mygameengine.SDLGraphicsProgram(SCRN_WIDTH,SCRN_HEIGHT)
   
# Load all script files.
dir = 'assets/scripts'
for filename in os.listdir(dir):
    f = os.path.join(dir, filename)
    if os.path.isfile(f):
        exec(open(f).read())
        
# Load all room files.
dir = 'assets/levels'
for filename in os.listdir(dir):
    f = os.path.join(dir, filename)
    if os.path.isfile(f):
        data = json.load(open(f))
        rooms[filename.split('.')[0]] = data
        

# Load init room
load_room('level_1', "assets/sprites/tilesets/space_tileset_1.bmp")

engine.view_hitboxes = False

while True:
    if engine.loop():
        break
    engine.clear()
    engine.delay(10);
    engine.flip();
