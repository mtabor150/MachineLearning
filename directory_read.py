import sys
import os.path
import re
import string

DEBUGGING = False

#get directory path
repo_path = os.path.dirname(os.path.abspath(__file__))

#get path of irsihbloggers files
blogs_path = repo_path + "/irishbloggers"

test_blogs_path = repo_path + "/test"

def get_blogger_names():
  #get name of each blogger (or directory)
  blogger_names =[]
  for filename in os.listdir (blogs_path):
    if(filename[0] != '.'):
        blogger_names.append(filename)

  #return list of blogger names
  return blogger_names
  #print names of file for each blogger

def get_blogger_blogs(blogger):
  blogger_path = blogs_path + "/" + blogger

  #get name of each blog for the blogger
  blogs_content = []
  for filename in os.listdir(blogger_path):
    blog_path = blogger_path +"/" + filename
    content = open(blog_path, 'r').read()

    new_content = remove_first_line(content)

    #print filename
    if DEBUGGING:
      print new_content

    blogs_content.append(content)
  return blogs_content

def get_test_blogs():
  blogs = dict()
  for filename in os.listdir(test_blogs_path):
    blog_num = filename[0:-4]
    blogs[blog_num] = open(test_blogs_path + "/" + filename, 'r').read()
  
  blogs2 = []
  for i in range(len(blogs)):
    blogs2.append(blogs[str(i+1)])
  return blogs2

def remove_first_line(text):
  pos = text.find('\n')
  new_str = text[pos+1:]
  return new_str

def tokenize_string(content):

  # .lower() returns a version with all upper case characters replaced with lower case characters.
  text = content.lower()
  words = [word.strip(string.punctuation) for word in text.split()]

  return words