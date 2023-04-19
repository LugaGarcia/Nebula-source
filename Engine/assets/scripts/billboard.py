# Constants
## Billboard class, which is a placeholer
class Billboard:
    def __init__(self, x, y, path, w, h):
        ## @var vx 
        # velocity of x
        self.vx = 0
        ## @var vy 
        # velocity of y
        self.vy = 0
        ## @var lifetime 
        # the time it takes for gameobject to destroy 
        self.lifetime = -1
        ## @var obj 
        # the gameobject created
        self.obj = mygameengine.GameObject("Billboard", x, y,
                                           path, w, h, 0, 0,
                                           self.update,
                                           0, 0, 0, 0, self)
        engine.instance_create(self.obj)

    ## update through game
    def update(self):
        if (self.lifetime > 0):
            self.lifetime -= 1
        if (self.lifetime ==0):
            self.destroy()
        
        self.obj.x += self.vx
        self.obj.y += self.vy
        pass
    
    ## destroys the gameobject itself
    def destroy(self):
        engine.instance_destroy(self.obj)
        del self
