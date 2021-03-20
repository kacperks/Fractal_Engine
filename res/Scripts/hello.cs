using System;
using Fractal;
using System.Collections.Generic;
using System.Runtime.InteropServices;


public class TestScript : FractalScript
{
	public float SpinSpeed = 90;
    public void Start() 
    {     
        Console.WriteLine("Script Started!");
    }

    public void Update(float deltatime, ref Transform transform) 
    {
      transform.Rotation.X += SpinSpeed * deltatime;
      transform.Rotation.Z += SpinSpeed * deltatime;
      transform.Position.X += 10 * deltatime;
    }
}