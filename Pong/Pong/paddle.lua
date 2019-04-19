Object = require "classic"

paddle = Object:extend()


-- paddle:new(x, y)
-- create a new paddle
-- @param x - x location
-- @param y - y location
-- @return none
function paddle:new(x, y)
    self.currPos = {x = x, y = y}
    self.startPos = {x = x, y = y}
    self.width = 10
    self.height = 80
end

-- paddle:hitRight(dt, ball)
-- bounce the ball from the right
-- @param dt - delta time
-- @param ball - the ball object
-- @return none
function paddle:hitRight(dt, ball)
    ball:bounce(-1, 1, dt)
    ball.currPos.x = ball.currPos.x - 10
end

-- paddle:hitLeft(dt, ball)
-- bounce the ball from the left
-- @param dt - delta time
-- @param ball - the ball object
-- @return none
function paddle:hitLeft(dt, ball)
    ball:bounce(-1, 1, dt)
    ball.currPos.x = ball.currPos.x + 10
end

-- paddle:draw()
-- draw the paddle as a rectangle
-- @param none
-- @return none
function paddle:draw()
    love.graphics.rectangle("fill", self.currPos.x, self.currPos.y, self.width, self.height)
end

-- paddle:moveUp()
-- moves the paddle up
-- @param none
-- @return none
function paddle:moveUp(dt) 
    self.currPos.y = self.currPos.y - (500 * dt)
end

-- paddle:moveDown()
-- moves the paddle down
-- @param none
-- return none
function paddle:moveDown(dt)
    self.currPos.y = self.currPos.y + (500 * dt)
end


