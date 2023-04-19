## Player script defined here.
import math

# Constants
SHOOT_TIME = 2
PLAYER_BBOX_W = 24
PLAYER_BBOX_H = 24
PLAYER_BBOX_X = int(-PLAYER_BBOX_W/2)
PLAYER_BBOX_Y = int(-PLAYER_BBOX_H/2)

PLAYER_SPR_W = 48
PLAYER_SPR_H = 48
PLAYER_SPR_X = int(-PLAYER_SPR_W/2)
PLAYER_SPR_Y = int(-PLAYER_SPR_H/2)

PLAYER_MOVE_SPD = 4
PLAYER_ROTATION_SPD = 5
BUL_SPD = 15

TILE_SIZE = 32
MAP_W = 784
solid_tiles = [0, 1, 2, 3, 4, 5, 6, 7, 15, 16, 17, 18, 19, 20, 21, 22, 23, 31, 32, 33, 34, 35]

## Bullet damage player shoots
PLAYER_BULLET_DMG = 1

## Class consisting of locatxion, score, level, shooting timer
class Player:
    def __init__(self, x, y):
        self.vx = 0
        self.vy = 0
        self.hp = 10
        self.score = 0
        self.level = 1
        self.shoot_timer = SHOOT_TIME
        self.obj = mygameengine.GameObject("Player", x+PLAYER_SPR_X, y+PLAYER_SPR_Y, 
                                            "assets/sprites/player_spritesheets/Player_FullHealth.bmp", PLAYER_SPR_W, PLAYER_SPR_H, PLAYER_SPR_X, PLAYER_SPR_Y,
                                            self.update,
                                            PLAYER_BBOX_X, PLAYER_BBOX_Y, PLAYER_BBOX_W, PLAYER_BBOX_H, self)
        self.dmg = PLAYER_BULLET_DMG
        engine.instance_create(self.obj)
                
    def update(self):
        if (self.hp <= 0):
            self.destroy()
            return

        ## Rotates the player based on keyboard input
        if (engine.key_left):
            self.obj.rotation -= PLAYER_ROTATION_SPD
        if (engine.key_a):
            self.obj.rotation -= PLAYER_ROTATION_SPD
        if (engine.key_right):
            self.obj.rotation += PLAYER_ROTATION_SPD
        if (engine.key_d):
            self.obj.rotation += PLAYER_ROTATION_SPD
        self.obj.rotation %= 360;

        ## Get the x and y speeds relative to player rotation
        joy_hat_x = math.sin(math.radians(self.obj.rotation))
        joy_hat_y = math.cos(math.radians(self.obj.rotation))
        
        ## If the player is pressing the up key, move in the direction they're facing
        if (engine.key_up or engine.key_w):
            self.vx = int(PLAYER_MOVE_SPD * joy_hat_x)
            self.vy = int(-PLAYER_MOVE_SPD * joy_hat_y)
        else:
            self.vx = 0
            self.vy = 0

        ## Check for if the player is attempting to move into a solid tile and prevent said movement
        ## X-Direction
        x_to_check = self.obj.x + self.vx
        if (self.vx > 0):
            x_to_check += int(PLAYER_BBOX_W/2)
        elif (self.vx < 0):
            x_to_check -= int(PLAYER_BBOX_W/2)

        x_coll = engine.tilemap_get_at_pixel(x_to_check, self.obj.y)
        if (x_coll in solid_tiles):
            self.vx = 0;

        ## Y-Direction
        y_to_check = self.obj.y + self.vy
        if (self.vy > 0):
            y_to_check += int(PLAYER_BBOX_H/2)
        elif (self.vy < 0):
            y_to_check -= int(PLAYER_BBOX_H/2)
        y_coll = engine.tilemap_get_at_pixel(self.obj.x, y_to_check)
        if (y_coll in solid_tiles):
            self.vy = 0  

        ## Update the player's position based on their velocity
        self.obj.x += self.vx
        self.obj.y += self.vy

        ## Handle player shooting
        if (engine.key_space):
            self.shoot_timer-=1
            if (self.shoot_timer == 0):
                o = Bullet(self, self.level, self.obj.x-int(PLAYER_SPR_X/2)+BULLET_BBOX_W, self.obj.y-int(PLAYER_SPR_Y/2)+BULLET_BBOX_H, self.obj.rotation)
                o.dmg = self.dmg
                o.vx = int(joy_hat_x * BUL_SPD)
                o.vy = int(joy_hat_y * BUL_SPD)
                self.shoot_timer = SHOOT_TIME
                engine.play_sound("assets/sounds/laserShoot.wav")
        
        ## Update the player's animation
        if (self.vx or self.vy):
            self.obj.anim = 0
        else:
            self.obj.anim = 1
        self.obj.frame += 0.25
        
        ## position the camera based on the player's new position and if they're at
        ## the edge of the map
        px_scr = self.obj.x - SCRN_WIDTH

        if (px_scr < 0):
            px_scr = 0
        elif (px_scr > MAP_W - SCRN_WIDTH):
            px_scr = MAP_W - SCRN_WIDTH
        engine.camera_x = px_scr
        
        px_scr = self.obj.y - (SCRN_HEIGHT + 60)
        if (px_scr < 0):
            px_scr = 0
        elif (px_scr > MAP_W - SCRN_HEIGHT):
            px_scr = MAP_W - SCRN_HEIGHT
        engine.camera_y = px_scr
        
    ## Damages player's health point by the given value
    def damage(self, dmg):
        self.hp -= dmg

    ## Destroys the gameobject itself
    def destroy(self):
        engine.instance_destroy_all(self.obj)
        Billboard(engine.camera_x, engine.camera_y , "assets/sprites/lose.bmp", 320, 240)
        engine.instance_destroy(self.obj)
        
        del self

    def addScore(self):
        self.score += 1

        if (self.level == 1 and self.score >= 3):
            engine.play_sound("assets/sounds/NextLevel.wav")
            load_room('level_2', "assets/sprites/tilesets/space_tileset_2.bmp")
            self.level = 2
            self.score = 0
            self.obj.x = 500
            self.obj.y = 500
        elif (self.level == 2 and self.score >= 5):
            engine.play_sound("assets/sounds/NextLevel.wav")
            load_room('level_3', "assets/sprites/tilesets/space_tileset_3.bmp")
            self.level = 3
            self.score = 0
            self.obj.x = 500
            self.obj.y = 850
        elif (self.level == 3 and self.score >= 8):
            engine.play_sound("assets/sounds/GameWon.wav")
            o = Billboard(engine.camera_x, engine.camera_y, "assets/sprites/win.bmp", 220, 187)
            
