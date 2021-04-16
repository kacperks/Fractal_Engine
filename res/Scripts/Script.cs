using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using Fractal;

public class TestScript : FractalScript
{
    public float Speed;
    public void Start()
    {
        Console.WriteLine("Script Started!");
        Speed = 20;
    }

    public void Update(float deltatime, ref Transform transform)
    {
       // transform.Rotation.Y += 10 * deltatime;
    }
}