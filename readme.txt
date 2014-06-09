JAPA – Just Another Paging Analyser

JAPA will compute or provide data that allows the computation of:
1. The ratio between the time taken to load a page and the time it is in use (for all pages, for code pages and for read-write pages)
2. The average of (1) between any arbitrary time period
3. An index value for every page (for all pages, for code pages and for read-write pages) that measures the intensity of memory access – total memory accesses/(page size x total time in use)
4. An index of the breadth of use for every page (for all pages, for code pages and for read-write pages) – total range accessed/page size
5. (3) and (4) will be available between any arbitrary time range
6. JAPA analyses XML data that complies with this DTD:

<!DOCTYPE pageanalysis [
<!ELEMENT pageanalysis (page*)>
<!ATTLIST pageanalysis version CDATA #FIXED "0.2">
<!ATTLIST pageanalysis xmlns CDATA #FIXED "http://cartesianproduct.wordpress.com">
<!ELEMENT page (code*, rw*)>
<!ATTLIST page frame CDATA #REQUIRED>
<!ATTLIST page in CDATA #REQUIRED>
<!ATTLIST page out CDATA #REQUIRED>
<!ELEMENT code CDATA #REQUIRED>
<!ATTLIST code address CDATA #REQUIRED>
<!ATTLIST code size CDATA #REQUIRED>
<!ELEMENT rw CDATA #REQUIRED>
<!ATTLIST rw address CDATA #REQUIRED>
<!ATTLIST rw size CDATA #REQUIRED>
]>

7. JAPA is licensed for reuse under version 2, or any later version at your discretion, of the GNU General Public Licence

8. JAPA is copyright (c) Adrian McMenamin, 2014

