#!/usr/bin/python2
import _VehicleAnalyze as va
import cPickle as pickle
import cv2


class IVehicleAnalyze:
    def __init__(self,model_dir,gpu_id,frameskip,numnull):
        self.__analyzer = va.VehicleAnalyze(model_dir,gpu_id,frameskip,numnull)

    def input(self,filepath):
        self.__analyzer.input(filepath)

    def get_trackers(self):
        self.trackers = []
        trackers =  self.__analyzer.get_trackers()
        print(trackers.size())

        for tracker in trackers:
            tr = {}
            tr["id"] = tracker.id
            tr["start_frame"] = tracker.start_frame
            tr["end_frame"] = tracker.end_frame
            tr["cls"] = tracker.cls
            tr["track"] = []
            for zone in tracker.track:
                tr["track"].append((zone.x,zone.y,zone.w,zone.h))

            self.trackers.append(tr)

        self.trackers = sorted(self.trackers,key=lambda tracker: tracker["start_frame"])
        return self.trackers
                

def run_0():
    model_dir = "/home/zqp/install_lib/models"
    vehicleAnalyzer = IVehicleAnalyze(model_dir,int(0),int(10),int(10))

    videopath = "/home/zqp/video/suidao.mp4"
    vehicleAnalyzer.input(videopath)
    trackers = vehicleAnalyzer.get_trackers()
    pickle.dump(trackers,open("save.pkl","w"))
    print len(trackers)

def addRectangle(im,current_trackers,frame_index):
    font = cv2.FONT_HERSHEY_SIMPLEX

    remove_trackers = []

    for tracker in current_trackers:
        print frame_index,"\t",tracker["start_frame"],"\t",tracker["end_frame"],"\t",len(tracker["track"])
        zone  = tracker["track"][frame_index-tracker["start_frame"]]
        cv2.rectangle(im,(zone[0],zone[1]),(zone[0]+zone[2],zone[1]+zone[3]),(0,0,255),3)
        label = str(tracker["id"])+":"+str(tracker["cls"])
        cv2.putText(im,label,(zone[0],zone[1]),font,1.0,(0,255,0),2)
        
        if tracker["end_frame"]<=frame_index+1:
            remove_trackers.append(tracker)

    for tracker in remove_trackers:
        current_trackers.remove(tracker)

def run_1():
    trackers = pickle.load(open("save.pkl"))
    for tracker in trackers:
        print tracker["start_frame"]

    videopath = "/home/zqp/video/suidao.mp4"
    cap = cv2.VideoCapture(videopath)

    frame_index = 0
    current_trackers = []
    while 1:
        ret,frame = cap.read()
        if not ret:
            break

        if len(trackers) and trackers[0]["start_frame"]<=frame_index:
            current_trackers.append(trackers[0])
            trackers.remove(trackers[0])

        addRectangle(frame,current_trackers,frame_index)

        cv2.imshow("im",frame)
        if cv2.waitKey(30)==27:
            break

        frame_index += 1

if __name__=="__main__":
    run_1()
