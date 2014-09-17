table = read.table("test-tweets.txt", sep="\t", quote="")
source("3Char.R")
vector = CountForAllIds(table)