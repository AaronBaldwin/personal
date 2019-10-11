<div class="chapter-summary">
  <div class="chapter-header">
  <?php
    echo "<h1>$formattedSelectedBookTitle</h1>";
    echo "<h2>
      <span><a href='$previousSectionUrl'>&#60;&#60;&#60; Previous</a></span>
      $formattedSelectedSection
      <span><a href='$nextSectionUrl'>Next &#62;&#62;&#62;</a></span>
      </h2>";
  ?>
  </div>
  <?php include("./books/{$selectedBook}/{$selectedSection}"); ?>
</div>
