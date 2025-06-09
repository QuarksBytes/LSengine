
pub use  syngine_parser;

mod logical_engine;
mod Design;

fn open_design(path:&str){
    let  _file = std::fs::File::open(path)
        .expect("Unable to open file");
    
   let componant =  syngine_parser::componant_parser::read_componant_from_file(path);
    println!("Componant: {:?}", componant);

}

#[cfg(test)]
mod tests {
    use crate::open_design;

   
    #[test]
    fn it_works() {
        open_design("ksnck.json");
    }
}
