Object = require "classic"

map = Object:extend() 

function map:new(w, h, offset)
    map.width = w
    map.height = h 
    map.offset = offset
end


function map:wallBounce(ball)
    ball:bounce(1, -1)
end


-- not needed? here?????
function map:checkBoundaries(ball, right, left)
    --map boundaries
    if ball.currPos.x >= (map.width + map.offset) - ball.size then
        left.score = left.score + 1
        ball:reset()
    end
    if ball.currPos.x <= map.offset then
        right.score = right.score + 1
        ball:reset()
    end
end

