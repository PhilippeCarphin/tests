import xml.etree.ElementTree as ET

tree = ET.parse('questions.xml')
root = tree.getroot()
print(root.tag)
print(root[0].text.strip())
for child in root:
    print(type(child.tag))
    print(child.tag)
    print(type(child.attrib))
    print(child.attrib)
