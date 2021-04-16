using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

[StructLayout(LayoutKind.Sequential)]
public struct Vector3
{

    public Single X;
    public Single Y;
    public Single Z;

    public Vector3(Single x, Single y, float z)
    {
        X = x;
        Y = y;
        Z = z;
    }

    public Vector3(Single v)
    {
        X = v;
        Y = v;
        Z = v;
    }
}

[StructLayout(LayoutKind.Sequential)]
public struct Transform
{
    private int Entity;
    public Vector3 Position;
    public Vector3 Rotation;
    public Vector3 Scale;
    public int EntityID { get { return Entity; } }
}

public struct EntityName
{
    private int Entity;
    public string Value;
    public int EntityID { get { return Entity; } }
}

public class Orbit3DScript
{
    static void Main(string[] args)
    {
        Console.WriteLine(args.Length);
    }
}

public class TestScript : Orbit3DScript
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