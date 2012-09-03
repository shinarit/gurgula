#!/usr/bin/env python
# -*- coding: utf-8 -*-

from Tkinter import *

def gridify(num):
  return (num + EditorWindow.GRID_DENSITY / 2) / EditorWindow.GRID_DENSITY * EditorWindow.GRID_DENSITY

class EditorWindow(Frame):
  CANVAS_SIZE = (800, 600)
  GRID_DENSITY = 5
  GRID_COLOR = "#eee"

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
    self.canvas.bind('a', self.deletePressed)
    
    self.gridEnabled = True
    
    if self.grid:
      self.drawGrid()
  
  def drawGrid(self):
    map(lambda x: self.canvas.create_line(x, 0, x, EditorWindow.CANVAS_SIZE[1] + 5, fill = EditorWindow.GRID_COLOR), 
        range(EditorWindow.GRID_DENSITY, EditorWindow.CANVAS_SIZE[0] + 1, EditorWindow.GRID_DENSITY))
    map(lambda y: self.canvas.create_line(0, y, EditorWindow.CANVAS_SIZE[0] + 5, y, fill = EditorWindow.GRID_COLOR), 
        range(EditorWindow.GRID_DENSITY, EditorWindow.CANVAS_SIZE[1] + 1, EditorWindow.GRID_DENSITY))

  def leftMousePressed(self, event):
    if self.gridEnabled:
      event.x = gridify(event.x)
      event.y = gridify(event.y)
    self.points.append((event.x, event.y))
    if 1 < len(self.points):
      self.lines.append(self.canvas.create_line(*(self.points[-1] + self.points[-2])))

  def rightMousePressed(self, event):
    if 0 != len(self.points):
      self.points.pop()
      if 0 != len(self.lines):
        self.canvas.delete(self.lines.pop())
      self.mouseMove(event)

  def mouseMove(self, event):
    self.canvas.delete(-999)
    if self.gridEnabled:
      event.x = gridify(event.x)
      event.y = gridify(event.y)

    if 0 != len(self.points):
      self.canvas.create_line(event.x, event.y, *self.points[-1], tags=-999, fill="gray")
    
  def deletePressed(self, event):
    print "delete pressed"
    canvas.delete(CURRENT)

if __name__ == '__main__':
  tk = Tk()
  ed = EditorWindow(tk)
  ed.grid()
  tk.mainloop()

