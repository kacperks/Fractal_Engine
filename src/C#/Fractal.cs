using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace Fractal
{
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
    public struct Color
    {
        public Single R;
        public Single G;
        public Single B;
        public Color(Single r, Single g, float b)
        {
            R = r;
            G = g;
            B = b;
        }

        public Color(Single v)
        {
            R = v;
            G = v;
            B = v;
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
    [StructLayout(LayoutKind.Sequential)]
    public struct PointLight
    {
        private int Entity;
        public Color color;
        public float Intensity;
        public int EntityID { get { return Entity; } }
    }


    public class FractalScript
    {
        static void Main(string[] args)
        {
            Console.WriteLine(args.Length);
        }
    }

}
