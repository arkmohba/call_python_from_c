"""py_module.py located in the working directory"""
import cpp_module

def set_name(pet: cpp_module.Pet, name: str):
    pet.setName(name)
    print(pet.getName())

