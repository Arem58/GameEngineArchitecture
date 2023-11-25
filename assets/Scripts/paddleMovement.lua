function paddleMovement(ballPosY, paddlePosY, paddleSpeedY)
    if ballPosY > paddlePosY then
        paddleSpeedY.value = 200 -- Mover hacia abajo
    elseif ballPosY < paddlePosY then
        paddleSpeedY.value = -200 -- Mover hacia arriba
    else
        paddleSpeedY.value = 0 -- Detenerse
    end
end
