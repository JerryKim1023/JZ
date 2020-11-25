
new ClipboardJS("#saveButton");
function saveButton() {
    $("#saveButton").text("playlist copied");
    setTimeout(function () {
        resetSaveButton();
    }, 2000)
}

function resetSaveButton() {
    if ($(window).width() <= 600) {
      $("#saveButton").text("Save");
    }
    else {
      $("#saveButton").text("Save playlist");
    }
  }
  resetSaveButton();
