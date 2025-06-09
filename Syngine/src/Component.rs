use crate::ComponentConfig;

enum  ComponentType {
    INPUT,
    OUTPUT
}

struct Component{
    pub name: String,
    pub description: String,
    pub width: u64,
    pub height: u64,
    pub component_type: ComponentType,
    pub logical: Option<ComponentConfig>,
    pub electrical: Option<ComponentConfig>,
    
}