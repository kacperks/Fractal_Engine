Vector3 = {
    X
    Y
    Z

    Vector3(x,y,z) 
        X = x
        Y = y
        Z = z
    end
    Vector3(v)
        X = v
        Y = v 
        Z = v
    end
}

Color = {
    R
    G
    B

    Color(r,g,b) 
        R = r
        G = g
        B = b
    end
    Color(v)
        R = v
        G = v 
        B = v
    end
}

Transform = {
    Entity
    Vector3 Position
    Vector3 Rotation
    Vector3 Scale
    EntityID { get { return Entity } }
}


PointLight = {
    Entity
    Color color
    Intensity
    EntityID { get { return Entity } }
}