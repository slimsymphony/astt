#!/bin/python
# script for processing leader/follower execution cache file. Generates html file with links etc.
import os, cPickle, time, sys, getopt, json, shutil
import datetime, collections, copy, re

xfilecounter = {}
ignored_machine_names = []
ignored_cases = ['Empty 4', 'Empty 3']

chronological = {} # dictionary of test cases in cronological order. {time: [iteration, case]}

RESULT_UIFREEZE = 'UI Freeze' # not used
RESULT_FREEZE = 'Freeze'
RESULT_PASSED = 'Passed'
RESULT_NORUN = 'No run'
RESULT_RESET = 'Dump files'
RESULT_FETCHING_XFILES = 'Crashfiles fetching not finished'

def addtoxfilescounter(client):
    global xfilecounter
    if not xfilecounter.has_key(client):
        xfilecounter[client] = 1
    else:
        xfilecounter[client] += 1

def createChronologicalResultHtml(resultDict, outfolder, resultfile, subdirectory):
    """ create single html per iteraton """ 
    print 'Creating html for each iteration'
    
    chronofile = resultfile + '_chr.html'
    c = open(os.path.join(os.path.join(outfolder, subdirectory), chronofile), 'w')
    c.write('<html>')

    outfolder = os.path.join(outfolder, subdirectory)
    od = collections.OrderedDict(sorted(chronological.items()))
    for k,v in od.iteritems():
        
        tcId = v[1]
        i = v[0]
        result = v[2]
        if result != 'Passed':
            c.write('<a href="%s">%s (iteration %s) <font style="color:#FF3300">(%s)</font></a><br>' % (getHtmlCaseNameForIteration(tcId, i), tcId, i, result))
        else:
            c.write('<a href="%s">%s (iteration %s) (%s)</a><br>' % (getHtmlCaseNameForIteration(tcId, i), tcId, i, result))

        fn = getHtmlCaseNameForIteration(tcId, i)
        if not os.path.isfile(os.path.join(outfolder, fn)):
            f = open(os.path.join(outfolder, fn), 'w')
            f.write('<html>')

        else:
            f = open(os.path.join(outfolder, fn), 'a')

        if resultDict.has_key(tcId) and resultDict[tcId].has_key(i):
            
            line = '<h3><a id="%s%s">%s Iteration %s</a></h3><br>' % (tcId, str(1), tcId ,str(i))

            for client in resultDict[tcId][i]:

                if client in ignored_machine_names:
                    continue

                # print '%s iteration %s for client %s' % (tcId, i, client)
                line += '<tr><td width="350" nowrap></td><td>%s</td><br>' % client
                
                line += '<td>'
                if not resultDict[tcId][i].has_key(client):
                    line += 'Not executed</td>'
                    continue

                clientRes = resultDict[tcId][i][client]
                # pop the result directory for clien
                if clientRes.has_key('ResultDir'):
                    if clientRes.has_key('Machine'): # leader has the machine name in results
                        result_dir = os.path.join('\\\\', clientRes.pop('Machine'), clientRes.pop('ResultDir'))
                    else:
                        result_dir = os.path.join('\\\\', client, clientRes.pop('ResultDir'))
                else:
                    print 'no resultdir! %s iteration %s for %s\n   %r' % (tcId, str(i), client, clientRes)
                    continue
                        
                # if result and video available
                if clientRes.has_key('Video') and clientRes.has_key('Result') and clientRes['Video'] != '':
                    res = clientRes.pop('Result')
                    vid = os.path.join(result_dir, clientRes.pop('Video'))
                            
                    if res == 'Passed':
                        #style="background:#80BFFF"
                        line += '<a style="color:#339900" href="\\\\%s">%s</a><br>' % (vid, res)
                    else:
                        line += '<a style="color:#FF3300" href="\\\\%s">%s</a><br>' % (vid, res)
                        if RESULT_RESET.lower() in res.lower() or 'reset' in res.lower():
                            line += '<a href="\\\\%s">Dump files folder</a><br>' % os.path.join(result_dir, 'crash_dumps')
                                
                # only result available 
                elif clientRes.has_key('Result'):
                    #### TEMP, remove video
                    if clientRes.has_key('Video'):
                        clientRes.pop('Video')
                            
                    res = clientRes.pop('Result')
                    if clientRes.has_key('Video'):
                        clientRes.pop('Video') ## Video is empty if gets here
                                
                    if res == 'Passed':
                        line += '<font">%s</font><br>' % res
                    else:
                        line += '<font style="color:#FF33FF">%s</font><br>' % res
                        if RESULT_RESET.lower() in res.lower() or 'reset' in res.lower():
                            line += '<a href="\\\\%s">Dump files folder</a><br>' % os.path.join(result_dir, 'crash_dumps')
                        
                if clientRes.has_key('Previous') and clientRes['Previous'] != None:
                    prev = clientRes.pop('Previous')
                    line += '<a href="%s">Previous case</a> (%s [%s])<br>' % (getHtmlCaseNameForIteration(prev[1], prev[0]), prev[1], prev[0])
                        
                if clientRes.has_key('Next') and clientRes['Next'] != None:
                    next = clientRes.pop('Next')
                    line += '<a href="%s">Next case</a> (%s [%s])<br>' % ( getHtmlCaseNameForIteration(next[1], next[0]), next[1], next[0])

                if client == 'Leader' and (len(resultDict[tcId]) > i): # if there' next itearation
                    line += '<a href="%s">Next iteration</a> (%s [%s])<br>' % ( getHtmlCaseNameForIteration(tcId, i+1), tcId, i+1)
                
                if client == 'Leader' and ( i > 1): # if there' previous itearation
                    line += '<a href="%s">Previous iteration</a> (%s [%s])<br>' % ( getHtmlCaseNameForIteration(tcId, i-1), tcId, i-1)

                for key in sorted(clientRes.iterkeys(), key=natural_key):
                            
                    if key.startswith('Capture'):
                        #line += '<img height="160px" width="120px" src="%s"/>' % os.path.join(result_dir, clientRes[key])
                        line += '<img src="%s"/>' % os.path.join(result_dir, clientRes[key])
                            
                    elif key == 'Duration':
                        try:
                            m, s = divmod(int(clientRes[key] ), 60)
                            line += '<br>%s %02d:%02d' % (key, m, s)
                            line += str(int(clientRes[key]))
                        except Exception as e:
                            print 'error adding duration client %s key %s clienRes[key] %s (%s)' % (client, key, clientRes[key], e.message)
                    elif key == 'EndTime':
                        line += '<br>%s %s' % (key,clientRes[key])
                    else:
                        line += '<br>%s %s' % (key,clientRes[key])
                            
                line += '</td></tr><br>----------------------------<br><br>\n'   
                
            f.write(line)
                
            f.close()

    c.close()
    
def natural_key(string_):
    return [int(s) if s.isdigit() else s for s in re.split(r'(\d+)', string_)]

def setPreviousNext(resultDict):
    """ go through the results, create a chronological order of the executions and set the previous / next case links to results """

    # get the chronological order of the cases
    for tcId in resultDict.keys():
        if tcId in ignored_cases:
            continue

        for i in range(1, len(resultDict[tcId]) + 1): # each iteration of tc
            if resultDict[tcId].has_key(i):
                endtime = resultDict[tcId][i]['Leader']['EndTime']
                t = datetime.datetime.strptime(endtime, "%Y-%m-%d %H:%M:%S")
                chronological[t] = [i, tcId, resultDict[tcId][i]['Leader']['Result']]
                for client in resultDict[tcId][i]:
                    if resultDict[tcId][i][client]['Result'] != 'Passed' and client != 'Leader':
                        chronological[t][2] += ' -- %s Result: %s' % (client, resultDict[tcId][i][client]['Result'])
                # print ' ---------------------- %s ' % str(t)

    od = collections.OrderedDict(sorted(chronological.items()))
    for k,v in od.iteritems():
        
        tcId = v[1]
        iteration = v[0]
        # print '---\ncurrent case %s (%s)' % (tcId, iteration)
        # resultDict[self.tcId][iteration][client]{'Result' : 'Failed', 'ResultLink' : '\\joo.avi'}
        #resultDict[tcId][iteration]['Leader'][
        i = od.keys().index(k)
        if i == 0:
            # print 'no previous case'
            resultDict[tcId][iteration]['Leader']['Previous'] = None
        elif i > 0:
            prevCaseId = od.values()[i-1][1]
            prevCaseIteration = od.values()[i-1][0]
            # print 'previous case %s (iteration %s)' % (prevCaseId, prevCaseIteration)
            resultDict[tcId][iteration]['Leader']['Previous'] = [prevCaseIteration, prevCaseId]

        if len(od.keys()) > (i + 1):
            nextCaseId = od.values()[i+1][1]
            nextCaseIteration = od.values()[i+1][0]
            # print 'next case %s (iteration %s)' % (nextCaseId, nextCaseIteration)
            resultDict[tcId][iteration]['Leader']['Next'] = [nextCaseIteration, nextCaseId]
        else:
            # print 'this was the last'
            resultDict[tcId][iteration]['Leader']['Next'] = None

def processFollowerResults(cachefile, outfolder, outputfile, addimages=False, addlinks=False, onepager=False, resfolder=None):
    max = 200
    
    #resultCacheFileName = os.path.join(core.FW_conf['cache_dir'], 'leader.cache')
    resultCacheFileName = cachefile
    if os.path.isfile(resultCacheFileName):
        resultDict = cPickle.load(open(resultCacheFileName, 'rb'))
        print('Loading existing results from cache...')
    else:
        resultDict = {}

    setPreviousNext(resultDict)
    resultDictCopy = copy.deepcopy(resultDict)
    
    # dump json version of the result dictionary
    b = open(os.path.join(outfolder, 'results.dump.txt'), 'w')
    b.write(json.dumps(resultDict, indent=4))
    b.close()
    
    durations = {}
    testcaserows = {}
    failedcaserows = {}
    freezedcaserows = {}
    xfilescaserows = {}

    # resultDict[self.tcId][iteration][client]{'Result' : 'Failed', 'ResultLink' : '\\joo.avi'}        
    for tcId in resultDict.keys():
        
        if tcId in ignored_cases:
            continue
        
        if not testcaserows.has_key(tcId):
            testcaserows[tcId] = ''
            
        case_has_failed_results = False
        case_has_x_files = False
        case_has_freezes = False
            
        clientrow = {}
        for i in range(1, len(resultDict[tcId]) + 1): # each iteration of tc
                
            if resultDict[tcId].has_key(i):

                for client in resultDict[tcId][i]:
                    if client in ignored_machine_names:
                        continue
                    
                    if not durations.has_key(client):
                        durations[client] = 0

                    #print 'client %s results for case %s[%s]' % (client, tcId, i)
                    if not clientrow.has_key(client):
                        clientrow[client] = '<tr><td width="350" nowrap></td><td>%s</td>' % client
                            
                    # populate missing results backwards
                    j = i - 1
                    while j >= 1:
                        #print resultDict[tcId][j][client]
                        if not resultDict[tcId][j].has_key(client):
                            clientrow[client] += '<td></td>'
                        else:
                            break
                        j -= 1
                                                
                    clientRes = resultDict[tcId][i][client]
                    clientrow[client] += '<td>'
                        
                    # pop the result directory for clien
                    if clientRes.has_key('ResultDir'):
                        if client == 'Leader' and resfolder:
                            result_dir = resfolder
                        else:
                            if clientRes.has_key('Machine'): # leader has the machine name in results
                                result_dir = os.path.join('\\\\', clientRes.pop('Machine'), clientRes.pop('ResultDir'))
                            else:
                                result_dir = os.path.join('\\\\', client, clientRes.pop('ResultDir'))
                    else:
                        print 'nou resultdir'
                        continue
                        result_dir = resfolder
                        
                    # if result and video available
                    if addlinks and clientRes.has_key('Video') and clientRes.has_key('Result') and clientRes['Video'] != '':
                        res = clientRes.pop('Result')
                        vid = os.path.join(result_dir, clientRes.pop('Video'))
                            
                        if res == 'Passed':
                            #style="background:#80BFFF"
                            clientrow[client] += '<a style="color:#339900" href="\\\\%s">%s</a><br>' % (vid, res)
                        else:
                            clientrow[client] += '<a style="color:#FF3300" href="\\\\%s">%s</a><br>' % (vid, res)
                            if RESULT_RESET.lower() in res.lower() or 'reset' in res.lower():
                                clientrow[client] += '<a href="\\\\%s">Dump files folder</a><br>' % os.path.join(result_dir, 'crash_dumps')
                                case_has_x_files = True
                                addtoxfilescounter(client)
                            elif RESULT_FREEZE.lower() in res.lower():
                                case_has_freezes = True
                                    
                            case_has_failed_results = True
                                
                    # only result available 
                    elif clientRes.has_key('Result'):
                        #### TEMP, remove video
                        if clientRes.has_key('Video'):
                            clientRes.pop('Video')
                            
                        res = clientRes.pop('Result')
                        if clientRes.has_key('Video'):
                            clientRes.pop('Video') ## Video is empty if gets here
                                
                        if res == 'Passed':
                            clientrow[client] += '<font">%s</font><br>' % res
                        else:
                            clientrow[client] += '<font style="color:#FF33FF">%s</font><br>' % res
                            if RESULT_RESET.lower() in res.lower() or 'reset' in res.lower():
                                clientrow[client] += '<a href="\\\\%s">Dump files folder</a><br>' % os.path.join(result_dir, 'crash_dumps')
                                case_has_failed_results = True
                                case_has_x_files = True
                                addtoxfilescounter(client)
                            elif RESULT_FREEZE.lower() in res.lower():
                                case_has_freezes = True
                            else:
                                case_has_failed_results = True

                    if clientRes.has_key('Previous') and clientRes['Previous'] != None:
                        prev = clientRes.pop('Previous')
                        clientrow[client] += '<a href="%s">Previous case</a> (%s [%s])<br>' % (getHtmlCaseNameForIteration(prev[1], prev[0]), prev[1], prev[0])
                    else:
                        clientrow[client] += '<br>'
                        
                    if clientRes.has_key('Next') and clientRes['Next'] != None:
                        next = clientRes.pop('Next')
                        clientrow[client] += '<a href="%s">Next case</a> (%s [%s])<br>' % ( getHtmlCaseNameForIteration(next[1], next[0]), next[1], next[0])

                    for key in sorted(clientRes.iterkeys(), key=natural_key):
                            
                        if key.startswith('Capture'):
                            if addimages:
                                #clientrow[client] += '<a href="%s"><img height="120px" width="80px" src="%s"/></a>' % (clientRes[key], clientRes[key])
                                clientrow[client] += '<img src="%s"/>' % os.path.join(result_dir, clientRes[key])
                                #clientrow[client] += '<a href="%s" target="_blank"><img height="120px" width="80px" src="%s"/></a>' % (clientRes[key], clientRes[key])
                                #clientrow[client] += '<img src="%s"/>' % (clientRes[key])
                            
                        elif key == 'Duration':
                            try:
                                m, s = divmod(int(clientRes[key] ), 60)
                                clientrow[client] += '<br>%s %02d:%02d' % (key, m, s)
                                durations[client] += int(clientRes[key])
                            except:
                                print 'error adding duration %s %s' % (client, clientRes[key])

                        elif key == 'EndTime':
                            # 2013-08-23 13:31:27
                            #if client == 'Leader':
                            #    foo = datetime.datetime.strptime(clientRes[key], "%Y-%m-%d %H:%M:%S")
                            #    chronological[foo] = [i, tcId]
                                
                            clientrow[client] += '<br>%s %s' % (key,clientRes[key])
                        else:
                            clientrow[client] += '<br>%s %s' % (key,clientRes[key])
                            
                    clientrow[client] += '</td>\n'    

            else:
                print ('no iteration %d for tc %d' % (i, tcId))
                    
        for client in clientrow:
            testcaserows[tcId] += clientrow[client]
            if case_has_failed_results:
                if not failedcaserows.has_key(tcId):
                    failedcaserows[tcId] = ''
                failedcaserows[tcId] += clientrow[client]
                if case_has_x_files:
                    if not xfilescaserows.has_key(tcId):
                        xfilescaserows[tcId] = ''
                    xfilescaserows[tcId] += clientrow[client]
                if case_has_freezes:
                    if not freezedcaserows.has_key(tcId):
                        freezedcaserows[tcId] = ''
                    freezedcaserows[tcId] += clientrow[client]
                    
    # flush results to disk
    resultfile = outputfile
            
    f = open(os.path.join(outfolder, resultfile), 'w')
    f.write('<html>')
    global xfilecounter
    for client in durations:
        m, s = divmod(durations[client], 60)
        h, m = divmod(m, 60)
        if xfilecounter.has_key(client):
            xfiles = 'Dump files generated %s' % xfilecounter[client]
        else:
            xfiles = 'No Dump files'
            
        print ('%s total execution time %03d:%02d:%02d -- %s' % (client, h, m, s, xfiles))
        f.write('%s total execution time %03d:%02d:%02d -- %s<br>' % (client, h, m, s, xfiles))
            
    f.write('<br>')
        
    iterations = '<tr><th style="width: 300px;">case</th><td></td>'
    for i in range(1,max):
        iterations = iterations + r'<td nowrap style="width: 250px;">%s</td>' % i
    iterations += "</tr>\n"
        
    if not addimages and onepager: # simplified, one page version
            
        f.write('<table border="1">\n')
        iterations = '<tr><th style="width: 300px;">case</th><td></td>'
        f.write(iterations)
            
        for tc in testcaserows:
            f.write('<tr><td width="350" nowrap>%s</td></tr>%s\n' % (tc,testcaserows[tc]))
                            
        f.write('</table>')
            
    else:
            
        files_dir = os.path.abspath(os.path.join(outfolder, resultfile) + '_files')
        if not os.path.exists(files_dir):
            os.makedirs(files_dir)

        createChronologicalResultHtml(resultDictCopy, outfolder, resultfile, files_dir)
        f.write('<a href="%s/%s%s">%s</a><br><br><br>' % (os.path.join(outfolder, files_dir), resultfile, '_chr.html', 'Chronological order'))
            
        # resultDict[self.tcId][iteration][client]{'Result' : 'Failed', 'ResultLink' : '\\joo.avi'}
        generatedPages = {}
                
        for tc in sorted(testcaserows.iterkeys()):
                
            if not generatedPages.has_key(tc):
                    
                generatedPages[tc] = {}
                filename = getTcFileName(tc)
                filename = '%s/%s' % (files_dir, filename)
                try:
                    r = open(r'%s' % filename, 'w')
                except Exception as e:
                    print 'tried writing tc %s. error:\n%s' %(tc, e.message)
                    sys.exit(1)
                        
                # freezedcaserows = {}
                # xfilescaserows = {}
                if freezedcaserows.has_key(tc):
                    f.write('<a href="%s">%s  <font style="color:#FF3300">(FREEZE IN RESULTS)</font></a><br>' % (filename, tc)) # main page link
                elif xfilescaserows.has_key(tc):
                    f.write('<a href="%s">%s  <font style="color:#FF3300">(Dump files in results)</font></a><br>' % (filename, tc)) # main page link
                elif failedcaserows.has_key(tc):
                    f.write('<a href="%s">%s  <font style="color:#FF33FF">(Failed cases)</font></a><br>' % (filename, tc)) # main page link
                else:
                    f.write('<a href="%s">%s</a><br>' % (filename, tc)) # main page link
                        
                r.write('<html>')
                r.write('<table border="1">\n')
                r.write(iterations)
                r.write('<tr><td width="350" nowrap>%s</td></tr>%s\n' % (tc,testcaserows[tc]))
                r.write('</table>')
                r.write('</html>')
                r.close()
            else:
                print 'tc %s twice on the results?' % tc
                sys.exit(1)
                
        pass
        
    f.write('</html>')
    f.close()
        
def getTcFileName(tc):
    # filter out illegal chars from tc name to get a suitable file name
    filename =  "".join(x for x in tc if x.isalnum()) # filter out illegal chars from filename
    return filename + ".html"

def getHtmlCaseNameForIteration(tcId, iteration):
    # return the html name where the results are for tcId / iteration
    filename = getTcFileName(tcId)
    return filename.replace('.html', '_%s.html' % str(iteration))
            
def printusage():
    print 'usage: \n\tpython %s [-i] [-l] [-o <outputfile>]' % sys.argv[0]
    print '\n'
    print '\t-i\tadd images to report'
    print '\t-l\tadd links to report'
    print '\t-s\tsingle html (cannot be used with images)'
    print '\t-o\tname of report file'
    sys.exit()

if __name__ == "__main__":

    if len(sys.argv) < 2:
        print 'no input cache file given. exit'
        sys.exit(-1)
        
    if not os.path.isfile(sys.argv[1]):
        print 'given file does not exist. exit'
        sys.exit(-2)
        
    argv = sys.argv[2:]
    try:
        opts, args = getopt.getopt(argv,"lisnho:r",["ofile=","resfolder="])
    except getopt.GetoptError:
        printusage()
        sys.exit(2)
    
    images = False
    links = False
    outputfile = None
    onepager = False
    resultfolder = None
    outfolder = None
    
    for opt, arg in opts:
        if opt == '-h':
            printusage()
        elif opt == '-l':
            links = True
        elif opt == '-i':
            images = True
        elif opt == '-s':
            onepager = True
        elif opt in ("-o", "--outfile"):
            outputfile = arg
        elif opt in ("-r", "--resfolder"):
            resultfolder = arg
        elif opt in ("-f", "--outfolder"):
            outfolder = arg
            
    if outfolder == None:
        outfolder = os.path.split(sys.argv[1])[0]
        
    if not outputfile:
        timestamp = time.strftime("%Y-%m-%d-%H%M%S")
        outname = 'mtbf_results_%s' % timestamp
        outputfile = outname + ".html"
        #resultfile = 'mtbf_results.html'
    else:
        outname = outputfile
        
    if os.path.isfile(os.path.join(outfolder, outputfile)):
        print '%s already exists.. deleting' % os.path.abspath(os.path.join(outfolder, outputfile))
        os.remove(os.path.join(outfolder, outputfile))
        
    if os.path.isdir(os.path.join(outfolder, outputfile + '_files')):
        print '%s directory exists.. deleting' % os.path.abspath(os.path.join(outfolder, outputfile + '_files'))
        shutil.rmtree(os.path.join(outfolder, outputfile + '_files'))
        
        
    processFollowerResults(sys.argv[1], outfolder, outputfile, images, links, onepager, resultfolder)

