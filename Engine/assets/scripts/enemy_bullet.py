# Constants
## Enemies bullets defined
EN_BULLET_BBOX_W = 4
EN_BULLET_BBOX_H = 4
EN_BULLET_BBOX_X = int(-EN_BULLET_BBOX_W/2)
EN_BULLET_BBOX_Y = int(-EN_BULLET_BBOX_H/2)

EN_BULLET_SPR_W = 8
EN_BULLET_SPR_H = 8
EN_BULLET_SPR_X = int(-EN_BULLET_SPR_W/2)
EN_BULLET_SPR_Y = int(-EN_BULLET_SPR_H/2)


BULLET_LIFETIME = 100

## Enemy bullet class
class EnemyBullet:
    def __init__(self, x, y, rotation):
        ## @var vx
        # the velocity x
        self.vx = 0
        ## @var vy
        # the velocity y
        self.vy = 0
        ## @var dmg
        # damage to player
        self.dmg = 1
        ## @var lifetime
        # the time gameobject gets destroyed
        self.lifetime = BULLET_LIFETIME
        ## @var obj
        # the gameobject itself being spawned
        self.obj = mygameengine.GameObject("EnemyBullet", x+EN_BULLET_SPR_X, y+EN_BULLET_SPR_Y,
                                           "assets/sprites/enemy_bullet.bmp", EN_BULLET_SPR_W, EN_BULLET_SPR_H, EN_BULLET_SPR_X, EN_BULLET_SPR_Y,
                                           self.update,
                                           EN_BULLET_BBOX_X, EN_BULLET_BBOX_Y, EN_BULLET_BBOX_W, EN_BULLET_BBOX_H, self)
        engine.instance_create(self.obj)
        self.obj.rotation = rotation

    ## updates through the game
    def update(self):
        self.obj.frame += 0.25
        self.lifetime -= 1
        self.obj.x += self.vx
        self.obj.y -= self.vy
        if (self.lifetime < 0):
            self.destroy()
        o = engine.instance_place(self.obj, "Player")
        if (o):
            engine.play_sound("assets/sounds/playerDeath.wav")
            o.damage(self.dmg)
            self.destroy() 
            return

        x_to_check = self.obj.x + self.vx
        if (self.vx > 0):
            x_to_check += int(EN_BULLET_BBOX_W/2)
        elif (self.vx < 0):
            x_to_check -= int(EN_BULLET_BBOX_W/2)

        x_coll = engine.tilemap_get_at_pixel(x_to_check, self.obj.y)
        if (x_coll in solid_tiles):
            self.destroy()
            return

        ## Y-Direction
        y_to_check = self.obj.y + self.vy
        if (self.vy > 0):
            y_to_check += int(EN_BULLET_BBOX_H/2)
        elif (self.vy < 0):
            y_to_check -= int(EN_BULLET_BBOX_H/2)
        y_coll = engine.tilemap_get_at_pixel(self.obj.x, y_to_check)
        if (y_coll in solid_tiles):
            self.destroy() 
            return
    
    ## Destroys the gameobject itself
    def destroy(self):
        engine.instance_destroy(self.obj)
        del self
        return
