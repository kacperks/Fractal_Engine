using System.Collections.Generic;
using System.Runtime.InteropServices;
using System;


    [StructLayout(LayoutKind.Sequential)]
    public struct Vector3{
            public Single X;
            public Single Y;
            public Single Z;

            public Vector3(Single x, Single y, Single z){
                X = x;
                Y = y;
                Z = z;
            }
            public Vector3(Single v){
                X = v;
                Y = v;
                Z = v;
            }
    }
    [StructLayout(LayoutKind.Sequential)]
    public struct Transform{
            private int entity;
            public Vector3 position;
            public Vector3 rotation;
            public Vector3 scale;
            public int EntityID { get; {return entity;} }
    }
    public class FractalScript{
        static void Main(string[] args){

        }
    }

public class TestScript : FractalScript
{
    public void Start(){
        Console.WriteLine("C# work!");
    }
}
