
# Constants
BULLET_BBOX_W = 4
BULLET_BBOX_H = 4
BULLET_BBOX_X = int(-BULLET_BBOX_W/2)
BULLET_BBOX_Y = int(-BULLET_BBOX_H/2)

BULLET_SPR_W = 32
BULLET_SPR_H = 32
BULLET_SPR_X = int(-BULLET_SPR_W/2)
BULLET_SPR_Y = int(-BULLET_SPR_H/2)


BULLET_LIFETIME = 30

## Player Bullet Class
class Bullet:
    def __init__(self, player, level, x, y, rotation):
        ## @var vx 
        # velocity of x
        self.vx = 0
        ## @var vy 
        # velocity of y
        self.vy = 0
        ## @var dmg 
        # damage of the bullet
        self.dmg = 1
        ## @var lifetime 
        # the time it takes for bullet to destroy
        self.lifetime = BULLET_LIFETIME
        ## @var player
        # the player object that shot this bullet
        self.player = player
        ## @var level
        # the level this bullet was fired in
        self.level = level
        ## @var obj 
        # the object that is created 
        self.obj = mygameengine.GameObject("Bullet", x+BULLET_SPR_X, y+BULLET_SPR_Y,
                                           "assets/sprites/bullet.bmp", BULLET_SPR_W, BULLET_SPR_H, BULLET_SPR_X, BULLET_SPR_Y,
                                           self.update,
                                           BULLET_BBOX_X, BULLET_BBOX_Y, BULLET_BBOX_W, BULLET_BBOX_H, self)

        engine.instance_create(self.obj)
        self.obj.rotation = rotation
    ## update through game
    def update(self):
        if (not (self.player.level == self.level)):
            self.destroy()
            return

        self.obj.frame += 0.25
        self.lifetime -= 1
        self.obj.x += self.vx
        self.obj.y -= self.vy
        if (self.lifetime < 0):
            self.destroy()
        o = engine.instance_place(self.obj, "Enemy")
        if (o):
            if (o.hp - self.dmg <= 0):
                self.player.addScore()
            o.damage(self.dmg)
            self.destroy()  
            return   

        x_to_check = self.obj.x + self.vx
        if (self.vx > 0):
            x_to_check += int(BULLET_BBOX_W/2)
        elif (self.vx < 0):
            x_to_check -= int(BULLET_BBOX_W/2)

        x_coll = engine.tilemap_get_at_pixel(x_to_check, self.obj.y)
        if (x_coll in solid_tiles):
            self.destroy()
            return

        # Y-Direction
        y_to_check = self.obj.y + self.vy
        if (self.vy > 0):
            y_to_check += int(BULLET_BBOX_H/2)
        elif (self.vy < 0):
            y_to_check -= int(BULLET_BBOX_H/2)
        y_coll = engine.tilemap_get_at_pixel(self.obj.x, y_to_check)
        if (y_coll in solid_tiles):
            self.destroy()
            return
            
    ## destroy the object itself
    def destroy(self):
        engine.instance_destroy(self.obj)
        del self
