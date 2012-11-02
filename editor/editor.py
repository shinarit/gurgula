#!/usr/bin/env python
# -*- coding: utf-8 -*-

from Tkinter import *

def gridify(num):
  return (num + EditorWindow.GRID_DENSITY / 2) / EditorWindow.GRID_DENSITY * EditorWindow.GRID_DENSITY

def Print(item):
  print item

def mirrorAround(center, point):
  return (point - center) * -1 + center

class EditorWindow(Frame):
  CANVAS_SIZE = (800, 600)
  GRID_DENSITY = 5
  GRID_COLOR = "#eee"
  SYMMETRY_PARAMS = {'state': HIDDEN, 'fill': "#aaa"}

  def __init__(self, root):
    Frame.__init__(self)

    self.root = root
    
    self.points = []
    self.lines = []
    
    self.canvas = Canvas(self, bg = 'white', width = EditorWindow.CANVAS_SIZE[0], height = EditorWindow.CANVAS_SIZE[1])
    self.canvas.grid()
    self.canvas.bind('<Button-1>', self.leftMousePressed)
    self.canvas.bind('<Button-3>', self.rightMousePressed)
    self.canvas.bind('<Motion>', self.mouseMove)
    self.canvas.bind('<Delete>', self.deletePressed)
    self.canvas.bind('<KeyPress-Control_L>', lambda event: self.setFixedAngle(True))
    self.canvas.bind('<KeyRelease-Control_L>', lambda event: self.setFixedAngle(False))
    self.canvas.bind('h', self.symmetrySettings)
    self.canvas.bind('v', self.symmetrySettings)
    self.canvas.bind('g', self.switchGrid)
    self.canvas.focus_set()
    
    self.symmetry = None
    self.symmetryLines = {'h': [], 'v': []}
    
    self.gridEnabled = True
    self.fixedAngle = False
    self.gridItems = []
    
    if self.gridEnabled:
      self.drawGrid()
  
  def symmetrySettings(self, event):
    if self.symmetry == event.char:
      toHide = event.char
      self.symmetry = None
    else:
      toHide = self.symmetry
      self.symmetry = event.char
      map(lambda line: self.canvas.itemconfig(line, state = NORMAL), self.symmetryLines[self.symmetry])
    if toHide:
      map(lambda line: self.canvas.itemconfig(line, state = HIDDEN), self.symmetryLines[toHide])
    self.mouseMove(event)

  def drawGrid(self):
    self.gridItems.extend(map(lambda x: self.canvas.create_line(x, 0, x, EditorWindow.CANVAS_SIZE[1] + 5, fill = EditorWindow.GRID_COLOR),
                          range(EditorWindow.GRID_DENSITY, EditorWindow.CANVAS_SIZE[0] + 1, EditorWindow.GRID_DENSITY)))
    self.gridItems.extend(map(lambda y: self.canvas.create_line(0, y, EditorWindow.CANVAS_SIZE[0] + 5, y, fill = EditorWindow.GRID_COLOR),
                          range(EditorWindow.GRID_DENSITY, EditorWindow.CANVAS_SIZE[1] + 1, EditorWindow.GRID_DENSITY)))

  def switchGrid(self, event):
    if self.gridEnabled:
      self.disableGrid()
    else:
      self.enableGrid()
    self.mouseMove(event)
  
  def enableGrid(self):
    self.gridEnabled = True
    map(lambda line: self.canvas.itemconfig(line, state = NORMAL), self.gridItems)

  def disableGrid(self):
    self.gridEnabled = False
    map(lambda line: self.canvas.itemconfig(line, state = HIDDEN), self.gridItems)

  def drawLines(self, orig, dest):
    #the normal line
    self.lines.append(self.canvas.create_line(*(orig + dest)))
    
    #the simmetry lines
    horizontalParams = EditorWindow.SYMMETRY_PARAMS.copy()
    verticalParams = EditorWindow.SYMMETRY_PARAMS.copy()
    if 'h' == self.symmetry:
      horizontalParams['state'] = NORMAL
    elif 'v' == self.symmetry:
      verticalParams['state'] = NORMAL
    self.symmetryLines['v'].append(self.canvas.create_line( mirrorAround(self.points[0][0], orig[0]), orig[1],
                                                            mirrorAround(self.points[0][0], dest[0]), dest[1],
                                                            **verticalParams))
    self.symmetryLines['h'].append(self.canvas.create_line( orig[0], mirrorAround(self.points[0][1], orig[1]),
                                                            dest[0], mirrorAround(self.points[0][1], dest[1]),
                                                            **horizontalParams))

  def leftMousePressed(self, event):
    if self.gridEnabled:
      event.x = gridify(event.x)
      event.y = gridify(event.y)
    self.points.append((event.x, event.y))
    if 1 < len(self.points):
      self.drawLines(self.points[-1], self.points[-2])

  def rightMousePressed(self, event):
    if 0 != len(self.points):
      self.points.pop()
      if 0 != len(self.lines):
        self.canvas.delete(self.lines.pop())
        self.canvas.delete(self.symmetryLines['v'].pop())
        self.canvas.delete(self.symmetryLines['h'].pop())
      self.mouseMove(event)

  def mouseMove(self, event):
    self.canvas.delete(-999)
    self.canvas.delete(-998)

    if self.fixedAngle:
      event.x, event.y = fixAngles(event.x, event.y, self.points[-1])

    if self.gridEnabled:
      event.x = gridify(event.x)
      event.y = gridify(event.y)

    if 0 != len(self.points):
      self.canvas.create_line(event.x, event.y, *self.points[-1], tags=-999, fill="gray")

      symmetryParams = EditorWindow.SYMMETRY_PARAMS.copy()
      symmetryParams['state'] = NORMAL
      symmetryParams['tags'] = -998   

      if 'v' == self.symmetry:
        self.canvas.create_line(mirrorAround(self.points[0][0], event.x), event.y,
                                mirrorAround(self.points[0][0], self.points[-1][0]), self.points[-1][1],
                                **symmetryParams)
      elif 'h' == self.symmetry:
        self.canvas.create_line(event.x, mirrorAround(self.points[0][1], event.y),
                                self.points[-1][0], mirrorAround(self.points[0][1], self.points[-1][1]),
                                **symmetryParams)

  def deletePressed(self, event):
    self.canvas.delete(*(item for item in self.canvas.find_withtag(CURRENT) if item in self.lines))

  def setFixedAngle(self, value):
    self.fixedAngle = value

if __name__ == '__main__':
  tk = Tk()
  ed = EditorWindow(tk)
  ed.grid()
  tk.mainloop()

