--main file
require "ball"
require "map"
require "paddle"
Object = require "classic"

left = paddle(40, 200)
right = paddle(580, 200)
left.score = 0
right.score = 0

ball = ball(300, 200)

map = map(600, 400, 20)

function love.update(dt)
    ball:update(dt)
    
    if love.keyboard.isDown("w") and left.currPos.y > map.offset then
        left:moveUp(dt)  
    end
    if love.keyboard.isDown("s") and left.currPos.y + left.height < map.height + map.offset then
        left:moveDown(dt)
    end
    if love.keyboard.isDown("up") and right.currPos.y > map.offset then
        right:moveUp(dt)
    end
    if love.keyboard.isDown("down") and right.currPos.y + right.height < map.height + map.offset then
        right:moveDown(dt)
    end

    if ball.currPos.x > right.currPos.x - ball.size and ball.currPos.y <= right.currPos.y + right.height and ball.currPos.y >= right.currPos.y - ball.size then
        right:hitRight(dt, ball)
    end
    if ball.currPos.x < left.currPos.x + 5 and ball.currPos.y <= left.currPos.y + left.height and ball.currPos.y >= left.currPos.y - ball.size then
        left:hitLeft(dt, ball)
    end    

    if ball.currPos.y <= map.offset then
        map:wallBounce(ball)
    end
    if ball.currPos.y >= (map.height + map.offset) - ball.size then
        map:wallBounce(ball)
    end

    map:checkBoundaries(ball, right, left)
end

function love.draw()
    ball:draw()
    left:draw()
    right:draw()

    scoreFont = love.graphics.newFont(30)

    love.graphics.rectangle("line", 20, 20, 600, 400)

    love.graphics.setFont(scoreFont)
    love.graphics.print(left.score .. " - " .. right.score, 280, 40)
end