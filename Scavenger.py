
import os
import math
import random
import pygame
from pygame.locals import *

sc_size = (1920,1200)
#sc_flags = pygame.FULLSCREEN
sc_flags = 0
sc_bits = 32

colormap = (
        (0xAB614E,0x2F373E,0x3D5A79,0x5385BB,0xA8BD9C),
        (0x9E7152,0x64585A,0x363E41,0x7A838A,0xCED0CB),
        (0x4C97A4,0x16342C,0x148739,0x1EB735,0x9EC5BF),
        (0x212426,0x5E3936,0x997764,0xC9B3A8,0xE1D4C7),
        (0xd8add9,0x9eafa5,0x889573,0xa1754c,0x001803)
)

class Spit():
    loc = [0,0]

    def __init__(self,loc,direction):
        self.direction = direction
        self.loc[0] = loc[0]
        self.loc[1] = loc[1]
        self.loc[0] = self.loc[0] + (32 * math.sin(direction) + 32 * math.cos(direction) )
        self.loc[1] = self.loc[1] + (32 * math.cos(direction) + 32 * math.sin(direction) )
        self.life = 32
        self.color = (255,255,255)

    def move(self):
        self.loc[0] = self.loc[0] + math.sin(direction) - math.cos(direction)
        self.loc[1] = self.loc[1] - math.sin(direction) + math.cos(direction)
        self.life = self.life - 1
        if self.life < 0:
            del self
    
    def draw(self,screen):
        pygame.draw.line(screen,self.color,self.loc,self.loc,1)
    

class obj:
    def _init_(self):
        pass

def rot_center(image, angle):
    """rotate an image while keeping its center and size - Needs square images"""
    orig_rect = image.get_rect()
    rot_image = pygame.transform.rotate(image, angle)
    rot_rect = orig_rect.copy()
    rot_rect.center = rot_image.get_rect().center
    rot_image = rot_image.subsurface(rot_rect).copy()
    return rot_image

def lerp(a,b,t):
    return ( a.r + (b.r - a.r) * t, a.g + (b.g - a.g) * t, a.b + (b.b - a.b) * t, a.a + (b.a - a.a) * t )

spits = []

try:
    pygame.init()
    pygame.mixer.init()
    screen=pygame.display.set_mode(sc_size,sc_flags,sc_bits)
    screen_rect=screen.get_rect()
    scx = screen.get_width() / 2 
    scy = screen.get_height() / 2 

    pygame.mixer.music.load(os.path.join('music','fsm-team-escp-quasarise.mp3'))
    pygame.mixer.music.play(loops=-1)

    ship = pygame.image.load(os.path.join('graphics','ship.png')).convert_alpha()
    maptiles = pygame.image.load(os.path.join('graphics','tiles.png')).convert_alpha()
    maptiles_rect = maptiles.get_rect()
    
    clock = pygame.time.Clock()

    rot = 0

    running = True
    while(running):
        for event in pygame.event.get():
            if event.type==pygame.QUIT:
                running=False
        keys = pygame.key.get_pressed()
        if keys[pygame.K_ESCAPE]:
            running = False

        rot = rot + 0.1
        if rot > 360:
            rot = rot - 360

        screen.fill( colormap[0][0] )

        colorfrom = pygame.Color( colormap[0][2] )
        colorto = pygame.Color( colormap[0][3] )
        for count in range(0,512):
            lerpcolor = lerp(colorfrom,colorto,count/512)
            pygame.draw.line(screen,lerpcolor,(scx-256+count,0),(scx-256+count,scy*2))

        maptiles_rect.center = screen_rect.center
        screen.blit(maptiles, [0,0])
        
        for spit in spits:
            spit.draw(screen)

        scaledrotatedship = pygame.transform.scale(rot_center(ship,rot),(128,128))
        scaledrotatedship_rect = scaledrotatedship.get_rect()
        scaledrotatedship_rect.center = screen_rect.center
        screen.blit(scaledrotatedship, scaledrotatedship_rect)

        spits.append( Spit((900,400) ,rot+(random.random()*2) ) )

        pygame.display.update()
        dt = clock.tick(60)

#        player.position.x += player.xSpeed * dt
#        player.position.y += player.ySpeed * dt
        
finally:
    pygame.quit()
            
