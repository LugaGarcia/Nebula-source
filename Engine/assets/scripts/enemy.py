# Constants
##Enemy scrpt defined
ENEMY_BBOX_W = 24
ENEMY_BBOX_H = 24
ENEMY_BBOX_X = int(-ENEMY_BBOX_W/2)
ENEMY_BBOX_Y = int(-ENEMY_BBOX_H/2)

ENEMY_SPR_W = 48
ENEMY_SPR_H = 48
ENEMY_SPR_X = int(-ENEMY_SPR_W/2)
ENEMY_SPR_Y = int(-ENEMY_SPR_H/2)

BULLET_SPAWN_TIME = 8
BULLET_VEL = 2

## Enemy class
class Enemy:
    def __init__(self, x, y):
        ## @var x_orig 
        # x middle position
        self.x_orig = x + ENEMY_SPR_X
        ## @var y_orig 
        # y middle position
        self.y_orig = y + ENEMY_SPR_Y
        ## @var ang_off 
        # the angular offset to turn circle
        self.ang_off =  1
        ## @var radius 
        # the radius of the enemy
        self.radius = 32
        ## @var vx
        # the velocity x
        self.vx = 0
        ## @var vy
        # the velocity y
        self.vy = 0
        ## @var hp
        # health point 
        self.hp = 50

        ## @var bullet_velocity
        # the velocity of the bullet
        self.bullet_velocity = BULLET_VEL
        ## @var bullet_spawn_time
        # spawn time of bullet
        self.bullet_spawn_time = BULLET_SPAWN_TIME
        ## @var bullet_spawn_timer
        # timer takes to spawn bullet
        self.bullet_spawn_timer = self.bullet_spawn_time
        ## @var obj
        # the gameobject itself
        self.obj = mygameengine.GameObject("Enemy", self.x_orig, self.y_orig,
                                            "assets/sprites/enemy.bmp", ENEMY_SPR_W, ENEMY_SPR_H, ENEMY_SPR_X, ENEMY_SPR_Y, self.update, 
                                            ENEMY_BBOX_X, ENEMY_BBOX_Y, ENEMY_BBOX_W, ENEMY_BBOX_H, self)
        engine.instance_create(self.obj)

    ## update through game
    def update(self):
        if (self.hp <= 0):
            self.destroy()
            return
        
        self.obj.rotation += self.ang_off

        joy_hat_x = math.sin(math.radians(self.obj.rotation*-1)) * self.radius
        joy_hat_y = math.cos(math.radians(self.obj.rotation*-1)) * self.radius

        self.obj.x -= int(joy_hat_x)
        self.obj.y -= int(joy_hat_y)

        if (self.bullet_spawn_timer > 0):
            self.bullet_spawn_timer-= 1
        else :
            o = EnemyBullet(self.obj.x-int(ENEMY_SPR_X/2)-10, self.obj.y-int(ENEMY_SPR_Y/2)-10, self.obj.rotation)
            o.vx = int(-1 * self.bullet_velocity * joy_hat_x)
            o.vy = int(self.bullet_velocity * joy_hat_y)
            self.bullet_spawn_timer = self.bullet_spawn_time
        self.obj.anim = 0
        self.obj.frame += 0.25

    ## Damages enemy's health point by the given value
    def damage(self, dmg):
        self.hp -= dmg

    ## Destroys the gameobject itself
    def destroy(self):
        engine.play_sound("assets/sounds/enemyDeath.wav")
        Explosion(self.obj.x + 12, self.obj.y + 12)
        engine.instance_destroy(self.obj)
        del self



