# Constants
# Explosion script defined
EXPLOSION_RADIUS = 16

## Class of Particle Explosion
class ExplosionParticle:
    def __init__(self, x, y):
        self.bounds = None
        ## @var vx
        # the velocity x
        self.vx = 0;
        ## @var vy
        # the velocity y
        self.vy = 0;
        ## @var obj
        # the gameobject itself being created
        self.obj = mygameengine.GameObject("ExplosionParticle", x, y, 
                                            "assets/sprites/explosion.bmp", EXPLOSION_RADIUS, EXPLOSION_RADIUS, 0, 0,
                                            self.update,
                                            0, 0, 0, 0, self)
        engine.instance_create(self.obj)

    ## updates through game
    def update(self):
        self.obj.frame += 0.3
        self.obj.x += int(self.vx)
        self.obj.y -= int(self.vy)
        if (self.obj.frame >= 8):
            self.destroy()
    ## Destroys the gameobject itself
    def destroy(self):
        engine.instance_destroy(self.obj)
        del self    

## Class of Explosion
class Explosion:
    def __init__(self, x, y):
        ## @var x
        # the position x
        self.x = x
        ## @var y
        # the position y
        self.y = y 
        ## @var obj
        # the gameobject that is created
        self.obj = mygameengine.GameObject("Explosion", x, y, 
                                            "", 0, 0, 0, 0, self.update,
                                            0, 0, 0, 0, self)
        engine.instance_create(self.obj)
        ## @var lifetime
        # the time it takes for gameobject to get destroyed
        self.lifetime = 20;
    
    ## updates through game
    def update(self):
        self.lifetime -= 1
        if (self.lifetime == 0):
            self.destroy()
            return
        ## @var x_off
        # the x position within explosion radius used for explosion     
        x_off = random.randrange(-EXPLOSION_RADIUS, EXPLOSION_RADIUS)
        ## @var y_off
        # the y position within explosion radius used for explosion     
        y_off =  random.randrange(-EXPLOSION_RADIUS, EXPLOSION_RADIUS)
        o = ExplosionParticle(self.x + x_off, self.y + y_off)
        o.vx = x_off/(EXPLOSION_RADIUS/2)
        o.vy = random.randrange(0, 2);

    ## Destroys the gameobject itself
    def destroy(self):
        engine.instance_destroy(self.obj)
        del self
