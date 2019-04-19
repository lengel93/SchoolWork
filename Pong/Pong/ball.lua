--https://github.com/rxi/classic
Object = require "classic"

ball = Object:extend()

ball_size = 30 

--- ball:new
-- creates new ball object
-- @param none
-- @return none
function ball:new(x, y)
    self.currPos = {x = x, y = y}
    self.startPos = {x = x, y = y}
    self.size = ball_size
    self.movement = {x = 250, y = 65}
    self.ismoving = false
end

--- ball:reset
-- This function resets the ball to the start of the board
-- @param none
-- @return none
function ball:reset()
    self.movement.x = 250
    self.movement.y = 65 * 0.5 + math.random(-10, 10) / 20
    self.currPos.x = self.startPos.x
    self.currPos.y = self.startPos.y
end

--- ball:hadCollision
-- Checks if ball had a collision with a paddle
-- @param paddle
-- @return false - if no collision, True - if collision
function ball:hadCollision(paddle)
    if self.currPos.x > paddle.startPos.x + paddle.width or paddle.startPos.x > self.currPos.x + self.size then
        return false
    end
    if self.currPos.y > paddle.startPos.y + paddle.height or paddle.startPos.y > self.currPos.y + self.size then
        return false
    end
    return true
end

--- ball:update
-- Updates balls speed
-- @param dt - delta time (time since last loop iteration)
-- @return none
function ball:update(dt)
    self.currPos.x = self.currPos.x + self.movement.x * dt 
    self.currPos.y = self.currPos.y + self.movement.y * dt
end

--- ball:bounce
-- Updates balls speed and direction when it bounces off a wall
-- @param dt - delta time (time since last loop iteration)
-- @return none
function ball:bounce(xdir, ydir, dt)
    self.movement.x = self.movement.x * 1.2 * xdir 
    self.movement.y = self.movement.y * 1.2 * ydir 
end

--- ball:draw
-- draws the ball object
-- @param none
-- @return none
function ball:draw()
    love.graphics.rectangle('fill', self.currPos.x, self.currPos.y, self.size, self.size)
end




