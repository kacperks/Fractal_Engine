using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using Fractal;
public class ShowCase : FractalScript
{
    public float Speed;
    public void Start() 
    {     
        Console.WriteLine("Yep");
        Speed = 50;
    }

    public void Update(float deltatime, ref Transform transform) 
    {
                transform.Rotation.Y += Speed * deltatime;
                transform.Rotation.Z += Speed * deltatime;
    }
}