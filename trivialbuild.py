#!/usr/bin/env python
# encoding: utf-8

import os
import sys
import subprocess
import argparse
from argparse import RawTextHelpFormatter


class TrivialBuilder:
    main_path = ""
    
        
    def move_to_project(self, path):
        self.main_path = os.getcwd()
        
        if path == "all":
            return True
        
        project_path = os.path.join(self.main_path, path)
        
        if os.path.exists(project_path):
            os.chdir(project_path)
            return True
        else:
            print
            print red("Quitting cowardly. Project does not exist: " + path)
            return False
        
    
    def exit_from_project(self):
        os.chdir(self.main_path)
    
    def cmake(self, projectname):
        if os.path.exists('CMakeLists.txt'):
            print yellow("Found Cmake file... Running cmake...")
            cmake_return = subprocess.call(["cmake", "."])
        
            if cmake_return:
                print
                print red("CMake failed.")
            else:
                print
                print green("CMake Complete. OK.")
                self.build(projectname)
        else:
            print
            print red("No CMakeLists.txt found. Quitting very cowardly.")
            
            
    def build(self, projectname):
        print blue("build action called on " + projectname) 
        
        run_cmake = False
        
        if not self.move_to_project(projectname):
            return
        
        if os.path.exists('Makefile'):
            print yellow("Found makefile. Building directly...")
            print
            
            make_return = subprocess.call("make")
            
            if make_return:
                print
                print red("Build failed.")
            else:
                print
                print green("Build Complete. OK.")
        else:
            print
            print red("No makefile found. Will attempt to run CMake...")
            
            run_cmake = True
                    
        self.exit_from_project()
        
        if run_cmake:
            self.cmake(projectname) 
    
    
    def buildrun(self, projectname):
        print "buildrun action called on " + projectname

    def rebuild(self, projectname):
        print "rebuild action called on " + projectname

    def clean(self, projectname):
        print "clean action called on " + projectname

    def superclean(self, projectname):
        print "clean action called on " + projectname

    def execute(self, projectname):
        print "execute action called on " + projectname

    def create(self, projectname):
        print "create action called on " + projectname

    def deploy(self, projectname):
        print "deploy action called on " + projectname
        
    def setup(self, projectname):
        print "setup action called on " + projectname

    def builddocs(self, projectname):
        print "builddocs action called on " + projectname


COLORS = (
    'BLACK', 'RED', 'GREEN', 'YELLOW',
    'BLUE', 'MAGENTA', 'CYAN', 'WHITE'
)


def color_text(text, color_name, bold=False):
    if color_name in COLORS:
        return '\033[{0};{1}m{2}\033[0m'.format(
            int(bold), COLORS.index(color_name) + 30, text)
    sys.stderr.write('ERROR: "{0}" is not a valid color.\n'.format(color_name))
    sys.stderr.write('VALID COLORS: {0}.\n'.format(', '.join(COLORS)))


def create_text_functions():
    '''Automatically generates text coloring function based on the COLORS array. 
    For each color a method with the same name in lower case is generated. So
    instead of calling color_text with parameters you can now call, say, 
    green("some text") directly. Bold version is currently not supported.
    '''
    
    def create_text_function(i):
        def template_text_function(text):
            return color_text(text, COLORS[i])
            
        template_text_function.__name__ = COLORS[i].lower()
        
        return template_text_function
            
    this = sys.modules[__name__]
    
    for i in range(0, len(COLORS)):
        func = create_text_function(i)
        
        setattr(this, func.__name__, func)
    

        

def main():
    trivialBuilder = TrivialBuilder()
    
    parser = argparse.ArgumentParser(
        description='Trivial Engine Build Tool.',
        epilog='Making developer life trivial.',
        formatter_class=RawTextHelpFormatter
    )
            
    commands = {
        'build' : {
            'help' : 'Build the project',
            'optional' : True
        },
        
        'buildrun' : {
            'help' : 'Build and run the project',
            'optional' : True
        },
        
        'rebuild' : {
            'help' : 'Rebuild the project',
            'optional' : True
        },
        
        'clean' : {
            'help' : 'Clean the project. Run make clean everywhere.',
            'optional' : True
        },
        
        'superclean' : {
            'help': 'Clean everything, even the cmake files.',
            'optional': True
        },
        
        'execute' : {
            'help' : 'Run the project',
            'optional' : True
        },
        
        'create' : {
            'help' : 'Create a new project with the given name',
            'optional' : False
        },
            
        'deploy' : {
            'help' : 'Deploy a project',
            'optional' : False
        },
            
        'setup' : {
            'help' : 'Setup trivial',
            'optional' : True
        },
        
        'builddocs' : {
            'help': 'Build documentation.'
        }
    }
    
    help_text = ["One of the following actions:"]
    help_text = ''.join(help_text + ['\n    ' + c + '\t - ' + commands[c]['help'] for c in commands])
            
    parser.add_argument('action',
        metavar='action',
        type=str,
        help=help_text,
        choices=commands
    )
                       
    parser.add_argument('projectname',
        metavar='projectname',
        type=str,
        default='all',
        nargs='?',
        help='Name of the project to perform action on. \nThis parameter is optional for some commands.'
    )
        
    args = parser.parse_args()
    
    getattr(trivialBuilder, args.action)(args.projectname)
    
    
if __name__ == '__main__':
    create_text_functions()
    
    main()




