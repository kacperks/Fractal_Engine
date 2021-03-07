using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

[StructLayout(LayoutKind.Sequential)]
public struct Vector3 {

    public Single X;
    public Single Y;
    public Single Z;

    public Vector3(Single x, Single y, float z) {
        X = x;
        Y = y;
        Z = z;
    }

    public Vector3(Single v) {
        X = v;
        Y = v;
        Z = v;
    }
}

[StructLayout(LayoutKind.Sequential)]
public struct Transform {
    private int Entity;
    public Vector3 Position;
    public Vector3 Rotation;
    public Vector3 Scale;
    public int EntityID { get { return Entity; } }
}



public class FractalScript
    static void Main(string[] args)
    {
        Console.WriteLine(args.Length);
    }   
}

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