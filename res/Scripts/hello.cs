using Fractal;
using System;

public class TestScript : FractalScript
{
    static void Main(string[] args)
    {
        Console.WriteLine(args.Length);
    }
    public void Start()
    {
        Console.WriteLine("Script Started!!");
    }

    public void Update(float deltatime, ref Transform transform , ref PointLight light)
    {
        transform.Rotation.Y += 10 * deltatime;
        transform.Rotation.X += 10 * deltatime;
        light.color.R += 10 * deltatime;
    }
}