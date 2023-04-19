# Constants
## Obstacle and walls scripts defined
EN_OBSTACLE_SPR_X = 8
EN_OBSTACLE_SPR_Y = 8
EN_OBSTACLE_BBOX_X = 0
EN_OBSTACLE_BBOX_Y = 0
EN_OBSTACLE_BBOX_W = 8
EN_OBSTACLE_BBOX_H = 8

OBSTACLE_LIFETIME = 100

## Obstacle class that flies around the map
class Obstacle:
    def __init__(self, x, y):
        ## @var vx
        # the velocity x
        self.vx = 0
        ## @var vy
        # the velocity y
        self.vy = 0
        ## @var dmg
        # the damage that will be given
        self.dmg = 1
        ## @var lifetime
        # the time it takes for gameobject to be destroyed
        self.lifetime = OBSTACLE_LIFETIME
        ## @var obj
        # the gameobject that is created
        self.obj = mygameengine.GameObject("Obstacle", x+EN_OBSTACLE_SPR_X, y+EN_OBSTACLE_SPR_Y,
                                           "assets/sprites/greyrock.bmp", EN_OBSTACLE_BBOX_W, EN_OBSTACLE_BBOX_H, 0, 0,
                                           self.update,
                                           EN_OBSTACLE_BBOX_X, EN_OBSTACLE_BBOX_Y, EN_OBSTACLE_BBOX_W, EN_OBSTACLE_BBOX_H, self)
        engine.instance_create(self.obj)

    ## updates through the game
    def update(self):
        self.obj.frame += 0.25

        self.lifetime -= 1
        self.obj.x += self.vx
        self.obj.y -= self.vy
        if (self.lifetime < 0):
            self.destroy()
        ##o = engine.instance_place(self.obj, "Enemy")
        ##if (o):
        ##    o.damage(self.dmg)
        ##    self.destroy()     
    
    ## Destroys the gameobject itself
    def destroy(self):
        engine.instance_destroy(self.obj)
        del self
