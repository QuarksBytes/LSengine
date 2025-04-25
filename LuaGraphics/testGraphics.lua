function draw(viewPort,pinsState)
    drawCircle(viewPort.width / 2, viewPort.height / 2, 50, "#ff0000")  -- Red circle
    drawRect(10, 10, viewPort.width - 20, viewPort.height - 20, "#00ff00")  -- Green rectangle
    drawLine(0, 0, viewPort.width, viewPort.height, "#0000ff")  -- Blue line

    print("Pins state:",pinsState.A0,pinsState.A1)

    setPin("A1",false)
end
