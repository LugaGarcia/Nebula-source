# Constants
## Item script and class defined
ITEM_SPR_X = 32
ITEM_SPR_Y = 32
ITEM_BBOX_X = 0
ITEM_BBOX_Y = 0
ITEM_BBOX_W = 32
ITEM_BBOX_H = 32

ITEM_LIFETIME = 30

# TODO probably add any possible buffs in the future
## Buff enum class
class Buff(Enum):
    Attack = 0


## item that includes power ups
class Item: 

    def __init__(self, x, y):
        ## @var vx 
        # velocity of x
        self.vx = 0
        ## @var vy 
        # velocity of y
        self.vy = 0
        ## @var lifetime 
        # time it takes for gameobject to destroy
        self.lifetime = ITEM_LIFETIME
        ## @var buffType 
        # the type of buff item contains
        self.buffType = Buff.Attack # BuffType Enum value
        ## @var buffAmount 
        # the value that is increased by the type of Buff
        self.buffAmount = 1
        ## @var obj 
        # the gameobject itself created
        self.obj = mygameengine.GameObject("Item", x + ITEM_SPR_X, y + ITEM_SPR_Y, 
                                            "assets/sprites/mystery_item.bmp", ITEM_BBOX_W, ITEM_BBOX_H, 0, 0,
                                            self.update,
                                            ITEM_BBOX_X, ITEM_BBOX_Y, ITEM_BBOX_W, ITEM_BBOX_H, self)
        engine.instance_create(self.obj)

    ## update through game
    def update(self):
        self.lifetime -= 1
        self.obj.x += self.vx
        self.obj.y -= self.vy
        if (self.lifetime < 0):
            self.destroy()
        o = engine.instance_place(self.bounds, "Player")
        if (o):
            o.receiveBuff(self.buffType, self.buffAmount)
            self.destroy()     

    ## Destroys the gameobject itself
    def destroy(self):
        engine.instance_destroy(self.obj)
        del self
