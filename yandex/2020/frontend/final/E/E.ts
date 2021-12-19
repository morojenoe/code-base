interface SupportedCSSProperties {
  width?: number;
  height?: number;
  flexGrow?: number;
  flexDirection?: "row" | "column";
  alignItems?: "stretch" | "baseline" | "center" | "flex-start" | "flex-end";
  justifyContent?: "center" | "flex-start" | "flex-end" | "space-between" 
    | "space-evenly";
}

const defaultValues = {
  flexDirection: "row",
  alignItems: "stretch",
  justifyContent: "flex-start"
}

interface MyNode {
  style: SupportedCSSProperties;
  children?: MyNode[];
}

interface NodeDimensionObject {
  x: number;
  y: number;
  width: number;
  height: number;
}

function solution(root: MyNode, css?: SupportedCSSProperties) {
  let res: NodeDimensionObject[] = [];
  if (!css) {
    res.push({
      x: 0, y: 0, width: root.style.width, height: root.style.height
    });
  }
  root.children.forEach(c => {
    c.style.
  })
}

module.exports = function() {

}
