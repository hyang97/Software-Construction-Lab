#!/usr/bin/python

import sys, locale, string
from optparse import OptionParser

def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION] ... FILE1 FILE2

Compare two sorted files line by line."""
    
    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-1", action="store_false", dest="column1", default=True,
                      help="suppress column 1 (lines unique to FILE1)")
    parser.add_option("-2", action="store_false", dest="column2", default=True,
                      help="suppress column 2 (lines unique to FILE2)")
    parser.add_option("-3", action="store_false", dest="column3", default=True,
                      help="suppress column 3 (lines that appear in both\
                      files)")
    parser.add_option("-u", action="store_true", dest="unsorted_input",
                      default=False, help="Runs comm with unsorted inputs,\
                      outputs lines in same order as input") 
    options, args = parser.parse_args(sys.argv[1:])

    try:
        column1 = options.column1
    except:
        parser.error("invalid option: {0}".
                     format(options.column1))
    try:
        column2 = options.column2
    except:
        parser.error("invalid option: {0}".
                     format(options.column2))
    try:
        column3 = options.column3
    except:
        parser.error("invalid option: {0}".
                     format(options.column3))
    try:
        unsorted_input = options.unsorted_input
    except:
        parser.error("invalid option: {0}".
                     format(options.unsorted_input))

    if len(args) != 2:
        parser.error("wrong number of operands")
    file1 = args[0]
    file2 = args[1]

    try:
        f1 = open(file1, 'r')
        f2 = open(file2, 'r')

        lines1 = f1.readlines()
        lines2 = f2.readlines()

        len1 = len(lines1)
        len2 = len(lines2)
        if unsorted_input:
            for l1 in lines1:
                notfound = True
                for l2 in lines2:
                    if(l1 == l2):
                        if column3:
                            sys.stdout.write("\t\t" + l1)
                            lines2.remove(l2)
                            notfound = False
                if column1 and notfound:
                    sys.stdout.write(l1)

            if column2:
                for l in lines2:
                    sys.stdout.write("\t" + l)
        else:
            i1 = 0
            i2 = 0
            while (i1 < len1) and (i2 < len2):
                if lines1[i1] == lines2[i2]:
                    if column3:
                        sys.stdout.write("\t\t" + lines1[i1])
                    i1+=1
                    i2+=1
                elif lines1[i1] < lines2[i2]:
                    if column1:
                        sys.stdout.write(lines1[i1])
                    i1+=1
                else:
                    if column2:
                        sys.stdout.write("\t" + lines2[i2])
                    i2+=1
            if i1 < len1:
                if column1:
                    while i1 < len1:
                        sys.stdout.write(lines1[i1])
                        i1+=1
            if i2 < len2:
                if column2:
                    while i2 < len2:
                        sys.stdout.write("\t" + lines2[i2])
                        i2+=1
                

    except IOError as e:
        parser.error("I/O error({0}): {1}".
                     format(e,errno, e.strerror))
if __name__ == "__main__":
    main()
