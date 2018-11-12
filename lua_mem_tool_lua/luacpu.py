import os, sys
import urllib2
import subprocess
import sys,imp
contents = urllib2.urlopen("http://gitlab.testplus.cn/snippets/14/raw").read()
_mod_fg = imp.new_module('FrameGraph')
exec contents in _mod_fg.__dict__
FrameGraph, Matcher = _mod_fg.FrameGraph, _mod_fg.Matcher


class Ctx:
  def __init__(self):
    self.fg = FrameGraph("us")
    self.ts = []
  
ptn_line = Matcher('\[L=.*\]\[\d\]\[\d+\]\[(?P<dEvent>\d)\]\[l=(?P<level>\d+)\]\[(?P<dTS>\d+)\](?P<sName>.*)');
with open(sys.argv[1], 'rb') as fp:
  #fg = FrameGraph("us")
  current_level = -1
  costs = [1e300]
  func = {}
  lss = []
  cur_ls = "eeeeeee"
  func[cur_ls] = Ctx()
  cfunmap = {}
  current_line = 0
  for line in fp:
    current_line = current_line+1
    line = line.strip()
    o = ptn_line.match(line)
    if not o:
      print "line not match: `%r`" % line
      continue
 
    cfun = o.sName.split()
    if len(cfun) == 2 and cfun[0] == 'CFUN':
        if cfun[1] in cfunmap:
            funname = cfunmap[ cfun[1] ]
        else:
            out = subprocess.check_output(['addr2line', "-Cf", "-e", '/data/app/server/bin/Server', cfun[1]]).split('\n')
            outname = ''
            if len(out) > 0:
                outname = out[0]
                
            cfunmap[ cfun[1] ] = outname
            funname = outname
        
        o.sName = funname
 

    if o.dEvent == 0:
      if func[cur_ls].ts: 
        func[cur_ls].fg.Update(o.dTS - func[cur_ls].ts[-1]["nowts"])
      func[cur_ls].fg.Enter(o.sName)
      func[cur_ls].ts.append({"nowts":o.dTS, "name":o.sName})
    else:
      func[cur_ls].fg.Update(o.dTS - func[cur_ls].ts[-1]["nowts"])
      func[cur_ls].fg.Leave()
      
      if o.level == 0 and func[cur_ls].ts[-1]["name"] != o.sName:
        print "ERROR fun name not equal %s-%s current_line:%d" %(o.sName, func[cur_ls].ts[-1]["name"], current_line)
      
      func[cur_ls].ts.pop()
      if func[cur_ls].ts: 
        func[cur_ls].ts[-1]["nowts"] = o.dTS
  
  for _ls in func:
    with open("luacpuhot.%s.html" % sys.argv[1], "wb") as fp:
      fp.write(func[_ls].fg.ToHTML().encode('utf8'))