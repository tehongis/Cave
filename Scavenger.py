
import os
import math
import random
import pygame
from pygame.locals import *

BG_COLOR = (25,33,48)
SC_SIZE = (1920,1080)
SC_FLAGS = pygame.FULLSCREEN
SC_BITS = 32

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
    


def rot_center(image, angle):
    """rotate an image while keeping its center and size - Needs square images"""
    orig_rect = image.get_rect()
    rot_image = pygame.transform.rotate(image, angle)
    rot_rect = orig_rect.copy()
    rot_rect.center = rot_image.get_rect().center
    rot_image = rot_image.subsurface(rot_rect).copy()
    return rot_image

spits = []

try:
    pygame.init()
    pygame.mixer.init()
    screen=pygame.display.set_mode(SC_SIZE,SC_FLAGS,SC_BITS)
    screen_rect=screen.get_rect()

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

        screen.fill(BG_COLOR)
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
            
