<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet version="1.0"
  xmlns:r="http://xmlresume.sourceforge.net/resume/0.0"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

  <xsl:import href="marg.xsl"/>

  <xsl:param name="skills.format">comma</xsl:param>
  <xsl:param name="skills.level.display">1</xsl:param>
  <xsl:param name="referees.display">1</xsl:param>
  <xsl:param name="referees.layout">compact</xsl:param>
  <xsl:param name="header.format">standard</xsl:param>
  <xsl:param name="interest.description.format">single-line</xsl:param>
  <xsl:param name="address.format">standard</xsl:param>
  <xsl:param name="title.separator">: </xsl:param>
  <xsl:param name="skills.separator">, </xsl:param>
  <xsl:param name="skills.suffix">.</xsl:param>
  <xsl:param name="skills.level.start"> (</xsl:param>
  <xsl:param name="skills.level.end">)</xsl:param>
  <xsl:param name="subjects.word">Subjects</xsl:param>
  <xsl:param name="subjects.format">comma</xsl:param>
  <xsl:param name="subjects.separator">, </xsl:param>
  <xsl:param name="subjects.suffix">.</xsl:param>
  <xsl:param name="subjects.result.display">1</xsl:param>
  <xsl:param name="subjects.result.start"> (</xsl:param>
  <xsl:param name="subjects.result.end">)</xsl:param>
  <xsl:param name="location.start"> (</xsl:param>
  <xsl:param name="location.end">)</xsl:param>
  <xsl:param name="description.para.separator"> &#x2014; </xsl:param>
  <xsl:param name="pub.author.separator">, </xsl:param>
  <xsl:param name="pub.item.separator">. </xsl:param>
  <xsl:param name="css.href">../../css/compact.css</xsl:param>
  <xsl:param name="css.embed">1</xsl:param>
  <xsl:param name="text.bullet.prefix">* </xsl:param>
  <xsl:param name="text.emphasis.start">*</xsl:param>
  <xsl:param name="text.emphasis.end">*</xsl:param>
  <xsl:param name="text.width">72</xsl:param>
  <xsl:param name="text.indent.width">4</xsl:param>
  <xsl:param name="header.line.pattern">rule</xsl:param>
  <xsl:param name="header.line.thickness">1pt</xsl:param>
  <xsl:param name="para.break.space">0.750em</xsl:param>
  <xsl:param name="half.space">0.4em</xsl:param>
  <xsl:param name="bullet.glyph">&#x2022;</xsl:param>
  <xsl:param name="bullet.space">1.0em</xsl:param>
  <xsl:param name="header.name.font.style">normal</xsl:param>
  <xsl:param name="header.name.font.weight">bold</xsl:param>
  <xsl:param name="header.name.font.size" select="$body.font.size"/>
  <xsl:param name="header.item.font.style">italic</xsl:param>
  <xsl:param name="footer.font.size">8pt</xsl:param>
  <xsl:param name="footer.font.family">serif</xsl:param>
  <xsl:param name="heading.font.size">10pt</xsl:param>
  <xsl:param name="heading.font.family">sans-serif</xsl:param>
  <xsl:param name="heading.font.weight">bold</xsl:param>
  <xsl:param name="heading.border.bottom.style">none</xsl:param>
  <xsl:param name="heading.border.bottom.width">thin</xsl:param>
  <xsl:param name="fineprint.font.size">8pt</xsl:param>
  <xsl:param name="emphasis.font.weight">bold</xsl:param>
  <xsl:param name="citation.font.style">italic</xsl:param>
  <xsl:param name="url.font.family">monospace</xsl:param>
  <xsl:param name="jobtitle.font.style">normal</xsl:param>
  <xsl:param name="jobtitle.font.weight">bold</xsl:param>
  <xsl:param name="degree.font.style">normal</xsl:param>
  <xsl:param name="degree.font.weight">bold</xsl:param>
  <xsl:param name="referee-name.font.style">italic</xsl:param>
  <xsl:param name="referee-name.font.weight">normal</xsl:param>
  <xsl:param name="employer.font.style">italic</xsl:param>
  <xsl:param name="employer.font.weight">normal</xsl:param>
  <xsl:param name="job-period.font.style">italic</xsl:param>
  <xsl:param name="job-period.font.weight">normal</xsl:param>
  <xsl:param name="job-subheading.font.style">italic</xsl:param>
  <xsl:param name="job-subheading.font.weight">normal</xsl:param>
  <xsl:param name="skillset-title.font.style">italic</xsl:param>
  <xsl:param name="skillset-title.font.weight">normal</xsl:param>
  <xsl:param name="degrees-note.font.style">italic</xsl:param>
  <xsl:param name="degrees-note.font.weight">normal</xsl:param>
  <xsl:param name="clearance-level.font.style">italic</xsl:param>
  <xsl:param name="clearance-level.font.weight">normal</xsl:param>
  <xsl:param name="gpa-preamble.font.style">italic</xsl:param>
  <xsl:param name="gpa-preamble.font.weight">normal</xsl:param>

</xsl:stylesheet>