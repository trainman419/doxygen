"//**************************************************************** \n"
"// You are free to copy the \"Folder-Tree\" script as long as you  \n"
"// keep this copyright notice: \n"
"// Script found in: http://www.geocities.com/Paris/LeftBank/2178/ \n"
"// Author: Marcelino Alves Martins (martins@hks.com) December '97. \n"
"//**************************************************************** \n"
" \n"
"//Log of changes: \n"
"//       17 Feb 98 - Fix initialization flashing problem with Netscape\n"
"//       \n"
"//       27 Jan 98 - Root folder starts open; support for USETEXTLINKS; \n"
"//                   make the ftien4 a js file \n"
"//       \n"
"// DvH:  Dec 2000 -  Made some minor changes to support external \n"
"//                   references\n"
" \n"
"// Definition of class Folder \n"
"// ***************************************************************** \n"
" \n"
"function Folder(folderDescription, tagName, hreference) //constructor \n"
"{ \n"
"  //constant data \n"
"  this.desc = folderDescription \n"
"  this.tagName = tagName\n"
"  this.hreference = hreference \n"
"  this.id = -1   \n"
"  this.navObj = 0  \n"
"  this.iconImg = 0  \n"
"  this.nodeImg = 0  \n"
"  this.isLastNode = 0 \n"
" \n"
"  //dynamic data \n"
"  this.isOpen = true \n"
"  this.iconSrc = \"ftv2folderopen.png\"   \n"
"  this.children = new Array \n"
"  this.nChildren = 0 \n"
" \n"
"  //methods \n"
"  this.initialize = initializeFolder \n"
"  this.setState = setStateFolder \n"
"  this.addChild = addChild \n"
"  this.createIndex = createEntryIndex \n"
"  this.hide = hideFolder \n"
"  this.display = display \n"
"  this.renderOb = drawFolder \n"
"  this.totalHeight = totalHeight \n"
"  this.subEntries = folderSubEntries \n"
"  this.outputLink = outputFolderLink \n"
"} \n"
" \n"
"function setStateFolder(isOpen) \n"
"{ \n"
"  var subEntries \n"
"  var totalHeight \n"
"  var fIt = 0 \n"
"  var i=0 \n"
" \n"
"  if (isOpen == this.isOpen) \n"
"    return \n"
" \n"
"  if (browserVersion == 2)  \n"
"  { \n"
"    totalHeight = 0 \n"
"    for (i=0; i < this.nChildren; i++) \n"
"      totalHeight = totalHeight + this.children[i].navObj.clip.height \n"
"      subEntries = this.subEntries() \n"
"    if (this.isOpen) \n"
"      totalHeight = 0 - totalHeight \n"
"    for (fIt = this.id + subEntries + 1; fIt < nEntries; fIt++) \n"
"      indexOfEntries[fIt].navObj.moveBy(0, totalHeight) \n"
"  }  \n"
"  this.isOpen = isOpen \n"
"  propagateChangesInState(this) \n"
"} \n"
" \n"
"function propagateChangesInState(folder) \n"
"{   \n"
"  var i=0 \n"
" \n"
"  if (folder.isOpen) \n"
"  { \n"
"    if (folder.nodeImg) \n"
"      if (folder.isLastNode) \n"
"        folder.nodeImg.src = \"ftv2mlastnode.png\" \n"
"      else \n"
"	  folder.nodeImg.src = \"ftv2mnode.png\" \n"
"    folder.iconImg.src = \"ftv2folderopen.png\" \n"
"    for (i=0; i<folder.nChildren; i++) \n"
"      folder.children[i].display() \n"
"  } \n"
"  else \n"
"  { \n"
"    if (folder.nodeImg) \n"
"      if (folder.isLastNode) \n"
"        folder.nodeImg.src = \"ftv2plastnode.png\" \n"
"      else \n"
"	  folder.nodeImg.src = \"ftv2pnode.png\" \n"
"    folder.iconImg.src = \"ftv2folderclosed.png\" \n"
"    for (i=0; i<folder.nChildren; i++) \n"
"      folder.children[i].hide() \n"
"  }  \n"
"} \n"
" \n"
"function hideFolder() \n"
"{ \n"
"  if (browserVersion == 1 || browserVersion == 3) \n"
"  { \n"
"    if (this.navObj.style.display == \"none\") \n"
"    {\n"
"      return\n"
"    }\n"
"    this.navObj.style.display = \"none\" \n"
"  } \n"
"  else \n"
"  { \n"
"    if (this.navObj.visibility == \"hidden\") \n"
"    {\n"
"      return \n"
"    }\n"
"    this.navObj.visibility = \"hidden\" \n"
"  } \n"
"   \n"
"  this.setState(0) \n"
"} \n"
" \n"
"function initializeFolder(level, lastNode, leftSide) \n"
"{ \n"
"  var j=0 \n"
"  var i=0 \n"
"  var numberOfFolders \n"
"  var numberOfDocs \n"
"  var nc \n"
"      \n"
"  nc = this.nChildren \n"
"   \n"
"  this.createIndex() \n"
" \n"
"  var auxEv = \"\" \n"
" \n"
"  if (browserVersion > 0) \n"
"    auxEv = \"<a href='javascript:clickOnNode(\"+this.id+\")'>\" \n"
"  else \n"
"    auxEv = \"<a>\" \n"
" \n"
"  if (level>0) \n"
"    if (lastNode) //the last 'brother' in the children array \n"
"    { \n"
"      this.renderOb(leftSide + auxEv + \"<img name='nodeIcon\" + this.id + \"' src='ftv2mlastnode.png' width=16 height=22 border=0></a>\") \n"
"      leftSide = leftSide + \"<img src='ftv2blank.png' width=16 height=22>\"  \n"
"      this.isLastNode = 1 \n"
"    } \n"
"    else \n"
"    { \n"
"      this.renderOb(leftSide + auxEv + \"<img name='nodeIcon\" + this.id + \"' src='ftv2mnode.png' width=16 height=22 border=0></a>\") \n"
"      leftSide = leftSide + \"<img src='ftv2vertline.png' width=16 height=22>\" \n"
"      this.isLastNode = 0 \n"
"    } \n"
"  else \n"
"    this.renderOb(\"\") \n"
"   \n"
"  if (nc > 0) \n"
"  { \n"
"    level = level + 1 \n"
"    for (i=0 ; i < this.nChildren; i++)  \n"
"    { \n"
"      if (i == this.nChildren-1) \n"
"        this.children[i].initialize(level, 1, leftSide) \n"
"      else \n"
"        this.children[i].initialize(level, 0, leftSide) \n"
"      } \n"
"  } \n"
"} \n"
" \n"
"function drawFolder(leftSide) \n"
"{ \n"
"  if (browserVersion == 2) \n"
"  { \n"
"    if (!doc.yPos)\n"
"    {\n"
"      doc.yPos=8 \n"
"    }\n"
"    doc.write(\"<layer id='folder\" + this.id + \"' top=\" + doc.yPos + \" visibility=hidden>\") \n"
"  } \n"
"  if (browserVersion == 3) \n"
"  {\n"
"    doc.write(\"<div id='folder\" + this.id + \"' style='visibility:hide;'>\") \n"
"  }\n"
"   \n"
"  doc.write(\"\\n<table \") \n"
"  if (browserVersion == 1) \n"
"  {\n"
"    doc.write(\" id='folder\" + this.id + \"' style='position:block;' \") \n"
"  }\n"
"  doc.write(\" border=0 cellspacing=0 cellpadding=0>\") \n"
"  doc.write(\"\\n<tr><td>\") \n"
"  doc.write(leftSide) \n"
"  this.outputLink() \n"
"  doc.write(\"<img name='folderIcon\" + this.id + \"' \") \n"
"  doc.write(\"src='\" + this.iconSrc+\"' border=0></a>\") \n"
"  doc.write(\"</td>\\n<td valign=middle nowrap>\") \n"
"  if (USETEXTLINKS) \n"
"  { \n"
"    this.outputLink() \n"
"    doc.write(this.desc + \"</a>\") \n"
"  } \n"
"  else \n"
"  {\n"
"    doc.write(this.desc) \n"
"  }\n"
"  if (this.tagName!=\"\")\n"
"  {\n"
"    doc.write(\" [external]\")\n"
"  }\n"
"  doc.write(\"</td>\")  \n"
"  doc.write(\"\\n</table>\\n\") \n"
"   \n"
"  if (browserVersion == 2) \n"
"  { \n"
"    doc.write(\"</layer>\") \n"
"  } \n"
"  if (browserVersion == 3) \n"
"  { \n"
"    doc.write(\"</div>\") \n"
"  } \n"
" \n"
"  if (browserVersion == 1) \n"
"  { \n"
"    this.navObj = doc.all[\"folder\"+this.id] \n"
"    this.iconImg = doc.all[\"folderIcon\"+this.id] \n"
"    this.nodeImg = doc.all[\"nodeIcon\"+this.id] \n"
"  } \n"
"  else if (browserVersion == 2) \n"
"  { \n"
"    this.navObj = doc.layers[\"folder\"+this.id] \n"
"    this.iconImg = this.navObj.document.images[\"folderIcon\"+this.id] \n"
"    this.nodeImg = this.navObj.document.images[\"nodeIcon\"+this.id] \n"
"    doc.yPos=doc.yPos+this.navObj.clip.height \n"
"  } \n"
"  else if (browserVersion == 3) \n"
"  {\n"
"    this.navObj = doc.getElementById(\"folder\"+this.id)\n"
"    this.iconImg = doc.images.namedItem(\"folderIcon\"+this.id)\n"
"    this.nodeImg = doc.images.namedItem(\"nodeIcon\"+this.id)\n"
"  }\n"
"} \n"
" \n"
"function outputFolderLink() \n"
"{ \n"
"  if (this.hreference) \n"
"  { \n"
"    doc.write(\"<a \")\n"
"    if (this.tagName)\n"
"    {\n"
"      doc.write(\"doxygen='\" + this.tagName + \"' \");\n"
"    }\n"
"    doc.write(\"href='\" + this.hreference + \"' TARGET=\\\"basefrm\\\" \") \n"
"    if (browserVersion > 0) \n"
"      doc.write(\"onClick='javascript:clickOnFolder(\"+this.id+\")'\") \n"
"    doc.write(\">\") \n"
"  } \n"
"  else \n"
"    doc.write(\"<a>\") \n"
"} \n"
" \n"
"function addChild(childNode) \n"
"{ \n"
"  this.children[this.nChildren] = childNode \n"
"  this.nChildren++ \n"
"  return childNode \n"
"} \n"
" \n"
"function folderSubEntries() \n"
"{ \n"
"  var i = 0 \n"
"  var se = this.nChildren \n"
" \n"
"  for (i=0; i < this.nChildren; i++){ \n"
"    if (this.children[i].children) //is a folder \n"
"      se = se + this.children[i].subEntries() \n"
"  } \n"
" \n"
"  return se \n"
"} \n"
" \n"
" \n"
"// Definition of class Item (a document or link inside a Folder) \n"
"// ************************************************************* \n"
" \n"
"function Item(itemDescription, tagName, itemLink) // Constructor \n"
"{ \n"
"  // constant data \n"
"  this.desc = itemDescription \n"
"  this.tagName = tagName\n"
"  this.link = itemLink \n"
"  this.id = -1 //initialized in initalize() \n"
"  this.navObj = 0 //initialized in render() \n"
"  this.iconImg = 0 //initialized in render() \n"
"  this.iconSrc = \"ftv2doc.png\" \n"
" \n"
"  // methods \n"
"  this.initialize = initializeItem \n"
"  this.createIndex = createEntryIndex \n"
"  this.hide = hideItem \n"
"  this.display = display \n"
"  this.renderOb = drawItem \n"
"  this.totalHeight = totalHeight \n"
"} \n"
" \n"
"function hideItem() \n"
"{ \n"
"  if (browserVersion == 1 || browserVersion == 3) { \n"
"    if (this.navObj.style.display == \"none\") \n"
"      return \n"
"    this.navObj.style.display = \"none\" \n"
"  } else { \n"
"    if (this.navObj.visibility == \"hidden\") \n"
"      return \n"
"    this.navObj.visibility = \"hidden\" \n"
"  }     \n"
"} \n"
" \n"
"function initializeItem(level, lastNode, leftSide) \n"
"{  \n"
"  this.createIndex() \n"
" \n"
"  if (level>0) \n"
"  {\n"
"    if (lastNode) //the last 'brother' in the children array \n"
"    { \n"
"      this.renderOb(leftSide + \"<img src='ftv2lastnode.png' width=16 height=22>\") \n"
"      leftSide = leftSide + \"<img src='ftv2blank.png' width=16 height=22>\"  \n"
"    } \n"
"    else \n"
"    { \n"
"      this.renderOb(leftSide + \"<img src='ftv2node.png' width=16 height=22>\") \n"
"      leftSide = leftSide + \"<img src='ftv2vertline.png' width=16 height=22>\" \n"
"    } \n"
"  }\n"
"  else \n"
"  {\n"
"    this.renderOb(\"\")   \n"
"  }\n"
"} \n"
" \n"
"function drawItem(leftSide) \n"
"{ \n"
"  if (browserVersion == 2)\n"
"  {\n"
"    doc.write(\"<layer id='item\" + this.id + \"' top=\" + doc.yPos + \" visibility=hidden>\")\n"
"  }\n"
"  else if (browserVersion == 3)\n"
"  {\n"
"    doc.write(\"<div id='item\" + this.id + \"' style='display:block;'>\")\n"
"  }\n"
"     \n"
"  doc.write(\"\\n<table \") \n"
"  if (browserVersion == 1)\n"
"  {\n"
"    doc.write(\" id='item\" + this.id + \"' style='position:block;' \")\n"
"  }\n"
"  doc.write(\" border=0 cellspacing=0 cellpadding=0>\\n\") \n"
"  doc.write(\"<tr><td>\") \n"
"  doc.write(leftSide) \n"
"  if (this.link!=\"\")\n"
"  {\n"
"    doc.write(\"<a href=\" + this.link + \">\") \n"
"  }\n"
"  doc.write(\"<img id='itemIcon\"+this.id+\"' \") \n"
"  doc.write(\"src='\"+this.iconSrc+\"' border=0>\") \n"
"  if (this.link!=\"\")\n"
"  {\n"
"    doc.write(\"</a>\")\n"
"  } \n"
"  doc.write(\"</td>\\n<td valign=middle nowrap>\") \n"
"  if (USETEXTLINKS && this.link!=\"\") \n"
"  {\n"
"    doc.write(\"<a href=\" + this.link + \">\" + this.desc + \"</a>\") \n"
"  }\n"
"  else \n"
"  {\n"
"    doc.write(this.desc) \n"
"  }\n"
"  if (this.tagName!=\"\")\n"
"  {\n"
"    doc.write(\" [external]\");\n"
"  }\n"
"  doc.write(\"\\n</table>\\n\") \n"
"   \n"
"  if (browserVersion == 2) \n"
"  {\n"
"    doc.write(\"</layer>\") \n"
"  }\n"
"  else if (browserVersion == 3) \n"
"  {\n"
"    doc.write(\"</div>\")\n"
"  }\n"
" \n"
"  if (browserVersion == 1) \n"
"  { \n"
"    this.navObj = doc.all[\"item\"+this.id] \n"
"    this.iconImg = doc.all[\"itemIcon\"+this.id] \n"
"  } \n"
"  else if (browserVersion == 2) \n"
"  { \n"
"    this.navObj = doc.layers[\"item\"+this.id] \n"
"    this.iconImg = this.navObj.document.images[\"itemIcon\"+this.id] \n"
"    doc.yPos=doc.yPos+this.navObj.clip.height \n"
"  } \n"
"  else if (browserVersion == 3) \n"
"  {\n"
"    this.navObj = doc.getElementById(\"item\"+this.id)\n"
"    this.iconImg = doc.images.namedItem(\"itemIcon\"+this.id)\n"
"  }\n"
"} \n"
" \n"
" \n"
"// Methods common to both objects (pseudo-inheritance) \n"
"// ******************************************************** \n"
" \n"
"function display() \n"
"{ \n"
"  if (browserVersion == 1 || browserVersion == 3) \n"
"  {\n"
"    this.navObj.style.display = \"block\" \n"
"  }\n"
"  else \n"
"  {\n"
"    this.navObj.visibility = \"show\"\n"
"  }\n"
"} \n"
" \n"
"function createEntryIndex() \n"
"{ \n"
"  this.id = nEntries \n"
"  indexOfEntries[nEntries] = this \n"
"  nEntries++ \n"
"} \n"
" \n"
"// total height of subEntries open \n"
"function totalHeight() //used with browserVersion == 2 \n"
"{ \n"
"  var h = this.navObj.clip.height \n"
"  var i = 0 \n"
"   \n"
"  if (this.isOpen) //is a folder and _is_ open \n"
"    for (i=0 ; i < this.nChildren; i++)  \n"
"      h = h + this.children[i].totalHeight() \n"
" \n"
"  return h \n"
"} \n"
" \n"
" \n"
"// Events \n"
"// ********************************************************* \n"
" \n"
"function clickOnFolder(folderId) \n"
"{ \n"
"  var clicked = indexOfEntries[folderId] \n"
" \n"
"  if (!clicked.isOpen) \n"
"    clickOnNode(folderId) \n"
" \n"
"  return  \n"
" \n"
"  if (clicked.isSelected) \n"
"    return \n"
"} \n"
" \n"
"function clickOnNode(folderId) \n"
"{ \n"
"  var clickedFolder = 0 \n"
"  var state = 0 \n"
" \n"
"  clickedFolder = indexOfEntries[folderId] \n"
"  state = clickedFolder.isOpen \n"
" \n"
"  clickedFolder.setState(!state) //open<->close  \n"
"} \n"
" \n"
"function preLoadIcons() \n"
"{\n"
"  var auxImg\n"
"  auxImg = new Image();\n"
"  auxImg.src = \"ftv2blank.png\";\n"
"  auxImg.src = \"ftv2doc.png\";\n"
"  auxImg.src = \"ftv2folderclosed.png\";\n"
"  auxImg.src = \"ftv2folderopen.png\";\n"
"  auxImg.src = \"ftv2lastnode.png\";\n"
"  auxImg.src = \"ftv2link.png\";\n"
"  auxImg.src = \"ftv2mlastnode.png\";\n"
"  auxImg.src = \"ftv2mnode.png\";\n"
"  auxImg.src = \"ftv2node.png\";\n"
"  auxImg.src = \"ftv2plastnode.png\";\n"
"  auxImg.src = \"ftv2pnode.png\";\n"
"  auxImg.src = \"ftv2vertline.png\";\n"
"}\n"
"\n"
"function initializeDocument() \n"
"{ \n"
"  preLoadIcons()\n"
"\n"
"  var ua = window.navigator.userAgent.toLowerCase();\n"
"  if ((ua.indexOf('msie')!=-1) && (navigator.version>=4))\n"
"  {\n"
"    browserVersion = 1  // IE >= 4.x\n"
"  }\n"
"  else if (ua.indexOf('opera')!=-1)\n"
"  {\n"
"    browserVersion = 3; // Opera\n"
"  }\n"
"  else if (ua.indexOf('gecko')!=-1)\n"
"  {\n"
"    browserVersion = 3; // NS6 or Mozilla\n"
"  }\n"
"  else if (ua.indexOf('mozilla')!=-1)\n"
"  {\n"
"    browserVersion = 2; // NS4\n"
"  }\n"
"  else\n"
"  {\n"
"    browserVersion = 0; // unknown or old browser\n"
"  }\n"
"\n"
"  foldersTree.initialize(0, 1, \"\") \n"
"  foldersTree.display()\n"
"  \n"
"  if (browserVersion > 0) \n"
"  { \n"
"    if(browserVersion != 3)\n"
"      doc.write(\"<layer top=\"+indexOfEntries[nEntries-1].navObj.top+\">&nbsp;</layer>\") \n"
" \n"
"    // close the whole tree \n"
"    clickOnNode(0) \n"
"    // open the root folder \n"
"    clickOnNode(0) \n"
"  } \n"
"} \n"
" \n"
"// Auxiliary Functions for Folder-Treee backward compatibility \n"
"// ********************************************************* \n"
" \n"
" \n"
"function gFld(description, tagName, hreference) \n"
"{ \n"
"  folder = new Folder(description, tagName, hreference) \n"
"  return folder \n"
"} \n"
" \n"
"function gLnk(description, tagName, linkData) \n"
"{ \n"
"  fullLink = \"\" \n"
" \n"
"  if (linkData!=\"\")\n"
"  {\n"
"    fullLink = \"'\"+linkData+\"' target=\\\"basefrm\\\"\" \n"
"  } \n"
" \n"
"  linkItem = new Item(description, tagName, fullLink)   \n"
"  return linkItem \n"
"} \n"
" \n"
"function insFld(parentFolder, childFolder) \n"
"{ \n"
"  return parentFolder.addChild(childFolder) \n"
"} \n"
" \n"
"function insDoc(parentFolder, document) \n"
"{ \n"
"  parentFolder.addChild(document) \n"
"} \n"
" \n"
"// Global variables \n"
"// **************** \n"
" \n"
"var USETEXTLINKS = 1\n"
"var indexOfEntries = new Array \n"
"var nEntries = 0 \n"
"var doc = document \n"
"var browserVersion = 0 \n"
"var selectedFolder=0\n"
"\n"
