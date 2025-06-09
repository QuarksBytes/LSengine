
struct Pin{
    pub name:String,
}

struct ComponentConfig {
    pub leftPins:vec<Pin>,
    pub rightPins:vec<Pin>,
    pub topPins:vec<Pin>,
    pub bottomPins:vec<Pin>,

    pub logic: String,
}