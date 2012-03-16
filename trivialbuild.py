#!/usr/bin/env python
# encoding: utf-8

import os
import sys
import argparse
from argparse import RawTextHelpFormatter


class TrivialBuilder:
    def build(self, projectname):
        print GREEN("build action called on ") + projectname
    
    def buildrun(self, projectname):
        print "buildrun action called on " + projectname

    def rebuild(self, projectname):
        print "rebuild action called on " + projectname

    def clean(self, projectname):
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
    def create_text_function(i):
        def template_text_function(text):
            return color_text(text, COLORS[i])
            
        template_text_function.__name__ = COLORS[i]
        
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
            'help' : 'Clean the project',
            'optional' : True
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
            'help' : 'Setup a project',
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




